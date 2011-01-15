/*! \file Ix_ConfigSection.h
 *  \brief 定义数据节点的值读写接口 Ix_ConfigSection
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.10.22
 */
#ifndef X3_XML_ICONFIGSECTION_H_
#define X3_XML_ICONFIGSECTION_H_

#include <XComPtr.h>

interface Ix_ConfigData;

//! 数据节点的值读写接口
/*! 可使用 CConfigIOSection 来更方便的使用本接口。\n
    本接口所操作的数据对象相当于是在树状层次结构中的一个数据节点，
    而 Ix_ConfigData 则对应于全部数据节点。
    \interface Ix_ConfigSection
    \ingroup _GROUP_PLUGIN_XML_
    \see CConfigIOSection, Ix_ConfigData
*/
interface Ix_ConfigSection
{
    //! 返回拥有者配置管理接口对象
    virtual Ix_ConfigData* GetData() const = 0;

    //! 返回内部数据是否合法
    /*!
        \return 其内部是否有对应的实际数据节点
    */
    virtual bool IsValid() const = 0;

    //! 得到值类型为字符串的配置项
    /*!
        \param name 配置属性名称
        \param defValue 默认值，当还没有对应的配置项时取为该值
        \return 该配置项的值
        \see SetString
    */
    virtual std::wstring GetString(const wchar_t* name, const wchar_t* defValue = L"") = 0;

    //! 设置值类型为字符串的配置项
    /*!
        \param name 配置属性名称
        \param value 新的值
        \return 是否改变了内容
        \see GetString
    */
    virtual bool SetString(const wchar_t* name, const wchar_t* value) = 0;

    //! 得到值类型为整数的配置项
    /*! 本函数会自动将取到的“true”和“false”转换为整数。
        \param name 配置属性名称
        \param defValue 默认值，当其内容为空串或没有时取为该值
        \return 该配置项的值
    */
    virtual int GetInt(const wchar_t* name, int defValue = 0) = 0;

    //! 设置值类型为整数的配置项
    /*!
        \param name 配置属性名称
        \param value 新的值
        \return 是否改变了内容
    */
    virtual bool SetInt(const wchar_t* name, int value) = 0;

    //! 得到值类型为长整数的配置项
    /*! 参数说明参考 GetInt()
    */
    virtual long GetInt32(const wchar_t* name, long defValue = 0) = 0;

    //! 设置值类型为长整数的配置项
    /*! 参数说明参考 SetInt()
    */
    virtual bool SetInt32(const wchar_t* name, long value) = 0;

    //! 得到值类型为无符号长整数的配置项
    /*! 参数说明参考 GetInt()
    */
    virtual ULONG GetUInt32(const wchar_t* name, ULONG defValue = 0) = 0;

    //! 设置值类型为无符号长整数的配置项
    /*! 参数说明参考 SetInt()
    */
    virtual bool SetUInt32(const wchar_t* name, ULONG value) = 0;

    //! 得到值类型为短整数的配置项
    /*! 参数说明参考 GetInt()
    */
    virtual short GetInt16(const wchar_t* name, short defValue = 0) = 0;

    //! 设置值类型为短整数的配置项
    /*! 参数说明参考 SetInt()
    */
    virtual bool SetInt16(const wchar_t* name, short value) = 0;

    //! 得到值类型为无符号短整数的配置项
    /*! 参数说明参考 GetInt()
    */
    virtual WORD GetUInt16(const wchar_t* name, WORD defValue = 0) = 0;

    //! 设置值类型为无符号短整数的配置项
    /*! 参数说明参考 SetInt()
    */
    virtual bool SetUInt16(const wchar_t* name, WORD value) = 0;

    //! 得到值类型为布尔的配置项
    /*!
        \param name 配置属性名称
        \param defValue 默认值，当其内容为空串或没有时取为该值
        \return 该配置项的值，内容为非零整数值或“true”时返回true，其余为false
    */
    virtual bool GetBool(const wchar_t* name, BOOL defValue) = 0;

    //! 设置值类型为布尔的配置项
    /*!
        \param name 配置属性名称
        \param value 新的值
        \return 是否改变了内容
    */
    virtual bool SetBool(const wchar_t* name, BOOL value) = 0;

    //! 得到值类型为浮点数的配置项
    /*!
        \param name 配置属性名称
        \param defValue 默认值，当其内容为空串或没有时取为该值
        \return 该配置项的值
    */
    virtual double GetDouble(const wchar_t* name, double defValue = 0) = 0;

    //! 设置值类型为浮点数的配置项
    /*!
        \param name 配置属性名称
        \param value 新的值
        \return 是否改变了内容
    */
    virtual bool SetDouble(const wchar_t* name, double value) = 0;

    //! 得到值类型为浮点数的配置项
    /*!
        参数说明参见 GetDouble()
    */
    virtual float GetFloat(const wchar_t* name, float defValue = 0) = 0;

    //! 设置值类型为浮点数的配置项
    /*!
        参数说明参见 SetDouble()
    */
    virtual bool SetFloat(const wchar_t* name, float value) = 0;

    //! 得到值类型为RGB颜色的配置项
    /*!
        \param name 配置属性名称
        \param defValue 默认值，当其内容没有包含三个整数时取为该值
        \return 该配置项的值，使用了 RGB(r,g,b) 宏
    */
    virtual COLORREF GetRGB(const wchar_t* name, COLORREF defValue) = 0;

    //! 设置值类型为RGB颜色值的配置项
    /*!
        \param name 配置属性名称
        \param value 新的值，仅取低6位的三个颜色分量
        \return 是否改变了内容
    */
    virtual bool SetRGB(const wchar_t* name, COLORREF value) = 0;

    //! 得到值类型为CMYK颜色值的配置项
    /*!
        \param[in] name 配置属性名称
        \param[out] c 读取成功时填充CMYK颜色值的C部分，失败时不改变其值
        \param[out] m 读取成功时填充CMYK颜色值的M部分，失败时不改变其值
        \param[out] y 读取成功时填充CMYK颜色值的Y部分，失败时不改变其值
        \param[out] k 读取成功时填充CMYK颜色值的K部分，失败时不改变其值
        \return 是否读取成功
    */
    virtual bool GetCMYK(const wchar_t* name, WORD& c, WORD& m, WORD& y, WORD& k) = 0;

    //! 设置值类型为CMYK颜色值的配置项
    /*!
        \param name 配置属性名称
        \param c CMYK颜色值的C部分
        \param m CMYK颜色值的M部分
        \param y CMYK颜色值的Y部分
        \param k CMYK颜色值的K部分
        \return 是否改变了内容
    */
    virtual bool SetCMYK(const wchar_t* name, WORD c, WORD m, WORD y, WORD k) = 0;

    //! 得到值类型为日期值的配置项
    /*!
        \param[in] name 配置属性名称
        \param[out] year 读取成功时填充年份(1980-2099)，失败时不改变其值
        \param[out] month 读取成功时填充月份(0-12)，失败时不改变其值
        \param[out] day 读取成功时填充日(0-31)，失败时不改变其值
        \return 是否读取成功
    */
    virtual bool GetDate(const wchar_t* name, int& year, int& month, int& day) = 0;

    //! 设置值类型为日期值的配置项
    /*!
        \param name 配置属性名称
        \param year 年份(1980-2099)
        \param month 月份(0-12)
        \param day 日(0-31)
        \return 是否改变了内容
    */
    virtual bool SetDate(const wchar_t* name, int year, int month, int day) = 0;

    //! 得到值类型为日期时间值的配置项
    /*!
        \param[in] name 配置属性名称
        \param[out] year 读取成功时填充年份(1980-2099)，失败时不改变其值
        \param[out] month 读取成功时填充月份(0-12)，失败时不改变其值
        \param[out] day 读取成功时填充日(0-31)，失败时不改变其值
        \param[out] hour 读取成功时填充小时(0-24)，失败时不改变其值
        \param[out] minute 读取成功时填充分钟(0-60)，失败时不改变其值
        \param[out] second 读取成功时填充秒(0-60)，失败时不改变其值
        \return 是否读取成功
    */
    virtual bool GetDateTime(const wchar_t* name, int& year, int& month, int& day, 
        int& hour, int& minute, int& second) = 0;

    //! 设置值类型为日期时间值的配置项
    /*!
        \param name 配置属性名称
        \param year 年份(1980-2099)
        \param month 月份(0-12)
        \param day 日(0-31)
        \param hour 小时(0-24)
        \param minute 分钟(0-60)
        \param second 秒(0-60)
        \return 是否改变了内容
    */
    virtual bool SetDateTime(const wchar_t* name, int year, int month, int day, 
        int hour, int minute, int second) = 0;

    //! 得到值类型为浮点数数组的配置项
    /*!
        \param[in] name 配置属性名称
        \param[out] items 要填充的浮点数数组，最多填充 count 个
        \param[in] count 数组的元素最大个数
        \return 读取到的元素个数，不超过 count
    */
    virtual long GetDoubleArray(const wchar_t* name, double* items, long count) = 0;

    //! 设置值类型为浮点数数组的配置项
    /*!
        \param name 配置属性名称
        \param items 要保存的浮点数数组
        \param count 数组的元素个数
        \return 是否设置成功
    */
    virtual bool SetDoubleArray(const wchar_t* name, const double* items, long count) = 0;
    
    //! 得到值类型为整数数组的配置项
    /*!
        \param[in] name 配置属性名称
        \param[out] items 要填充的整数数组，最多填充 count 个
        \param[in] count 数组的元素最大个数
        \return 读取到的元素个数，不超过 count
    */
    virtual long GetIntArray(const wchar_t* name, long* items, long count) = 0;

    //! 设置值类型为整数数组的配置项
    /*!
        \param name 配置属性名称
        \param items 要保存的整数数组
        \param count 数组的元素个数
        \return 是否设置成功
    */
    virtual bool SetIntArray(const wchar_t* name, const long* items, long count) = 0;
    
    //! 得到值类型为二进制缓冲的配置项
    /*!
        \param[in] name 配置属性名称
        \param[out] buf 要填充的缓冲，最多填充 size 字节
        \param[in] size 缓冲的最大长度
        \return 读取到的缓冲字节长度，不超过 size
    */
    virtual long GetBinary(const wchar_t* name, LPVOID buf, long size) = 0;

    //! 设置值类型为二进制缓冲的配置项
    /*!
        \param name 配置属性名称
        \param buf 要保存的缓冲
        \param size 缓冲的字节长度
        \return 是否设置成功
    */
    virtual bool SetBinary(const wchar_t* name, LPCVOID buf, long size) = 0;
};

#endif // X3_XML_ICONFIGSECTION_H_
