/*! \file XModuleItem.h
 *  \brief Define the base class of single instance classes. (for internal use only)
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_MODULEITEM_H_
#define X3_PLUGINIMPL_MODULEITEM_H_

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief the base class of single instance classes.
 *  \internal
 */
class CModuleItem
{
protected:
    CModuleItem() : m_index(-1)
    {
    }
    virtual ~CModuleItem()
    {
    }

    //! Add self to the single instance stack.
    void AddModuleItem()
    {
        m_index = InterlockedDecrement(&Index());   // support concurrent insert.
        if (m_index >= 0)
        {
            Items()[m_index] = this;                // only one thread can do it.
        }
    }

public:
    //! Free all single instance objects when this plugin is unloading.
    static void ClearModuleItems()
    {
        if (Items())
        {
            for (int i = Index(); i < MaxCount(); i++)
            {
                if (i >= 0 && Items()[i] )
                {
                    delete Items()[i];
                    Items()[i] = NULL;
                }
            }
            Index() = 0;

            delete[] Items();
            Items() = NULL;
        }
    }

    //! Init the single instance stack. _xGetModuleInterface will call it.
    static void InitModuleItems(long nCount)
    {
        if (NULL == Items() && nCount > 0)
        {
            MaxCount() = max(nCount, MaxCount());
            Index() = MaxCount();
            Items() = new CModuleItem*[MaxCount()];
        }
    }

private:
    long    m_index;    // index in the single instance stack.

    static long& MaxCount()
    {
        static long s_count = 0;
        return s_count;
    }
    static long& Index()
    {
        static long s_index = 0;
        return s_index;
    }
    static CModuleItem**& Items()
    {
        static CModuleItem** s_pItems = NULL;
        return s_pItems;
    }
};

#endif // X3_PLUGINIMPL_MODULEITEM_H_
