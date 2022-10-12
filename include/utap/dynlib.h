#ifndef UTAP_DYNLIB_H
#define UTAP_DYNLIB_H

/**
 * A thin wrapper to provide unified interface across platforms and avoid pollution with macros.
 */

class library_t
{
    struct state_t;
    state_t* pImpl;

public:
    /** Loads a dynamically linked library with specified name (path).
     * If loading fails, it will attempt to load with an OS-specific extension if no extension is given.
     * Throws std::runtime_error upon errors.
     */
    library_t(const char* name);
    /** Unloads the library. Outputs errors into stderr if any, when compiled with debug info. */
    ~library_t() noexcept;
    library_t(const library_t&) = delete;
    library_t(library_t&&) noexcept = default;
    library_t& operator=(const library_t&) = delete;
    library_t& operator=(library_t&&) noexcept = default;

    /** Finds the symbol in the library. Throws std::runtime_error upon errors. */
    void* get_symbol(const char* name);
};

#endif  // UTAP_DYNLIB_H
