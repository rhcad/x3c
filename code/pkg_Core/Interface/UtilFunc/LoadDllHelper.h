/*! \file LoadDllHelper.h
 *  \brief Define helper class to load library: LoadDllHelper
 *  \author Zhang Yungui, X3 C++ PluginFramework
 *  \date   2011.7.10
 */
#ifndef UTILFUNC_LOADDLLHELPER_H_
#define UTILFUNC_LOADDLLHELPER_H_

//! Helper class to load library.
/*! Use this to declare local variable in functions,
    then the library will be auto unload when leave from the function.
    \ingroup _GROUP_UTILFUNC
*/
class LoadDllHelper
{
public:
    //! Constructor.
    /*!
        \param filename file name of the library to be loaded immediately.
        \param assign a optional pointer to a variable that receives the library handle.
    */
    LoadDllHelper(const wchar_t* filename = NULL, HMODULE* assign = NULL)
        : m_hmod(NULL), m_assign(assign), m_loadnew(false)
    {
        if (filename)
        {
            Load(filename);
        }
    }

    //! Destructor which will auto unload the library.
    ~LoadDllHelper()
    {
        Unload();
    }

    //! Unload the library.
    void Unload()
    {
        if (m_hmod)
        {
            if (m_loadnew)
            {
                FreeLibrary(m_hmod);
            }
            m_hmod = NULL;

            if (m_assign)
            {
                *m_assign = NULL;
            }
        }
    }

    //! Load a library.
    bool Load(const wchar_t* filename)
    {
        Unload();

        m_hmod = GetModuleHandleW(filename);
        m_loadnew = !m_hmod;
        if (!m_hmod)
        {
            m_hmod = LoadLibraryW(filename);
        }
        if (m_assign)
        {
            *m_assign = m_hmod;
        }

        return m_hmod != NULL;
    }

    //! Return the module handle.
    HMODULE GetHandle() const
    {
        return m_hmod;
    }

    //! Return a import function.
    PROC GetFunc(const char* name) const
    {
        return m_hmod ? GetProcAddress(m_hmod, name) : NULL;
    }

private:
    HMODULE     m_hmod;
    HMODULE*    m_assign;
    bool        m_loadnew;
};

#endif // UTILFUNC_LOADDLLHELPER_H_