/*! \file XModuleItem.h
 *  \brief 定义单实例对象基类，内部文件
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.19
 */
#ifndef X3_PLUGINIMPL_MODULEITEM_H_
#define X3_PLUGINIMPL_MODULEITEM_H_

/*! \ingroup _GROUP_PLUGIN_CORE2_
 *  \brief 本模块内单实例对象基类，仅内部使用
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

    //! 添加自身到单实例对象链表
    void AddModuleItem()
    {
        m_index = InterlockedDecrement(&Index());   // 其他线程可同时添加
        if (m_index >= 0)
        {
            // Items[index] 只会被一个线程操作
            Items()[m_index] = this;
        }
    }

public:
    //! 在本模块卸载时，释放(delete)所有单实例对象
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

    //! 初始化单实例对象堆栈( _xGetModuleInterface 会调用本函数)
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
    long    m_index;    //!< 在单实例对象堆栈中的顺序，越早越大

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
