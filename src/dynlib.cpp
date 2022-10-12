#include "utap/dynlib.h"

#include <filesystem>
#include <stdexcept>

#ifndef NDEBUG
#include <iostream>
#endif

#if defined(__linux__) || defined(__APPLE__)
#include <dlfcn.h>

#if defined(__linux__)
static const auto dll_extension = std::string{".so"};
#elif defined(__APPLE__)
static auto dll_extension = std::string{".dylib"};
#else
#error "Unsupported target OS"
#endif

struct library_t::state_t
{
    void* handle{nullptr};

    state_t(const char* name): handle{dlopen(name, RTLD_NOW | RTLD_LOCAL)}
    {
        if (handle == nullptr) {
            auto path = std::filesystem::path{name};
            if (path.extension().string() == dll_extension)
                throw std::runtime_error(dlerror());
            else {
                path = name + dll_extension;
                handle = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
                if (handle == nullptr)
                    throw std::runtime_error(dlerror());
            }
        }
    }
    ~state_t() noexcept
    {
        if (handle) {
            auto res [[maybe_unused]] = dlclose(handle);
            handle = nullptr;
#ifndef NDEBUG
            if (res)
                std::cerr << dlerror() << std::endl;
#endif
        }
    }
    state_t(const state_t&) = delete;
    state_t(state_t&&) = delete;
    state_t& operator=(const state_t&) = delete;
    state_t& operator=(state_t&&) = delete;
};

void* library_t::get_symbol(const char* name)
{
    auto res = dlsym(pImpl->handle, name);
    if (!res)
        throw std::runtime_error(dlerror());
    return res;
}

#elif defined(_WIN32) || defined(__MINGW32__)

#include <sstream>
#include <windows.h>

static std::string get_error_message(const char* msg, DWORD err)
{
    auto ss = std::ostringstream{};
    ss << msg << " 0x" << std::hex << err;
    LPTSTR lpMessage = nullptr;
    DWORD sz =
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      nullptr, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMessage, 0, nullptr);
    if (sz > 0 && lpMessage != nullptr) {
        ss << ": " << lpMessage;
        LocalFree(lpMessage);
    }
    return ss.str();
}

static const auto dll_extension = std::string{".dll"};

struct library_t::state_t
{
    HMODULE handle;
    explicit state_t(const char* name): handle{LoadLibrary(TEXT(name))}
    {
        if (handle == nullptr) {
            auto err = GetLastError();
            auto path = std::filesystem::path{name};
            if (path.extension().string() == dll_extension)
                throw std::runtime_error(get_error_message("Failed to open dynamic library", err));
            else {
                path = name + dll_extension;
                handle = LoadLibrary(TEXT(path.string().c_str()));
                if (handle == nullptr)
                    throw std::runtime_error(get_error_message("Failed to open dynamic library", GetLastError()));
            }
        }
    }
    ~state_t() noexcept
    {
        if (handle) {
            BOOL res [[maybe_unused]] = FreeLibrary(handle);
#ifndef NDEBUG
            if (!res)
                std::cerr << get_error_message("Failed to close dynamic library", GetLastError()) << std::endl;
#endif
        }
    }

    state_t(const state_t&) = delete;
    state_t(state_t&&) = default;
    state_t& operator=(const state_t&) = delete;
    state_t& operator=(state_t&&) = default;
};

void* library_t::get_symbol(const char* name)
{
    void* res = (void*)GetProcAddress(pImpl->handle, name);
    if (res == nullptr)
        throw std::runtime_error(get_error_message("Failed to find symbol", GetLastError()));
    return res;
}

#else
#error "Unsupported target OS"
#endif

library_t::library_t(const char* name): pImpl{new state_t{name}} {}
library_t::~library_t() noexcept { delete pImpl; }
