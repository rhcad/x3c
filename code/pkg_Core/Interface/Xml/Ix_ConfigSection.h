/*! \file Ix_ConfigSection.h
 *  \brief Define the configure data node interface: Ix_ConfigSection
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3_XML_ICONFIGSECTION_H_
#define X3_XML_ICONFIGSECTION_H_

#include <XComPtr.h>

class Ix_ConfigData;

//! The configure data node interface.
/*! Use Cx_ConfigSection instead of using this interface.\n
    This interface object is represented as a data node in hierarchical structure nodes.\n
    Ix_ConfigData object is represented as all nodes.
    \interface Ix_ConfigSection
    \ingroup _GROUP_PLUGIN_XML_
    \see Cx_ConfigSection, Ix_ConfigData
*/
class Ix_ConfigSection : public Ix_Object
{
public:
    X3DEFINE_IID(Ix_ConfigSection)

    //! Return the owner object.
    virtual Ix_ConfigData* GetData() const = 0;

    //! Return true if the internal data is valid (has actual internal node).
    virtual bool IsValid() const = 0;

    //! Get a field value as string type.
    /*!
        \param name the field name.
        \param defValue default value if the field hasn't value.
        \return the field value.
        \see SetString
    */
    virtual std::wstring GetString(const wchar_t* name, const wchar_t* defValue = L"") = 0;

    //! Set a field value as string type.
    /*!
        \param name the field name.
        \param value the new field value.
        \return true if the field value changed.
        \see GetString
    */
    virtual bool SetString(const wchar_t* name, const wchar_t* value) = 0;

    //! Get a field value as integer type.
    /*! This function will automatic convert "true" and "false" value to integer.
        \param name the field name.
        \param defValue default value if the field hasn't value or has empty string value.
        \return the field value.
    */
    virtual int GetInt(const wchar_t* name, int defValue = 0) = 0;

    //! Set a field value as integer type.
    /*!
        \param name the field name.
        \param value the new field value.
        \return true if the field value changed.
    */
    virtual bool SetInt(const wchar_t* name, int value) = 0;

    //! \copydoc GetInt()
    virtual long GetInt32(const wchar_t* name, long defValue = 0) = 0;

    //! \copydoc SetInt()
    virtual bool SetInt32(const wchar_t* name, long value) = 0;

    //! \copydoc GetInt()
    virtual ULONG GetUInt32(const wchar_t* name, ULONG defValue = 0) = 0;

    //! \copydoc SetInt()
    virtual bool SetUInt32(const wchar_t* name, ULONG value) = 0;

    //! \copydoc GetInt()
    virtual short GetInt16(const wchar_t* name, short defValue = 0) = 0;

    //! \copydoc SetInt()
    virtual bool SetInt16(const wchar_t* name, short value) = 0;

    //! \copydoc GetInt()
    virtual WORD GetUInt16(const wchar_t* name, WORD defValue = 0) = 0;

    //! \copydoc SetInt()
    virtual bool SetUInt16(const wchar_t* name, WORD value) = 0;

    //! Get a field value as bool type.
    /*! This function will automatic convert "true" and "false" value to bool value.
        \param name the field name.
        \param defValue default value if the field hasn't value or has empty string value.
        \return the field value.
    */
    virtual bool GetBool(const wchar_t* name, int defValue) = 0;

    //! Set a field value as bool type.
    /*!
        \param name the field name.
        \param value the new field value.
        \return true if the field value changed.
    */
    virtual bool SetBool(const wchar_t* name, int value) = 0;

    //! Get a field value as floating-point type.
    /*!
        \param name the field name.
        \param defValue default value if the field hasn't value or has empty string value.
        \return the field value.
    */
    virtual double GetDouble(const wchar_t* name, double defValue = 0) = 0;

    //! Set a field value as floating-point type.
    /*!
        \param name the field name.
        \param value the new field value.
        \return true if the field value changed.
    */
    virtual bool SetDouble(const wchar_t* name, double value) = 0;

    //! \copydoc GetDouble()
    virtual float GetFloat(const wchar_t* name, float defValue = 0) = 0;

    //! \copydoc SetDouble()
    virtual bool SetFloat(const wchar_t* name, float value) = 0;

    //! Get a field value as COLORREF type.
    /*!
        \param name the field name.
        \param defValue default value if the field value not contains three integers.
        \return the field value as 0x00bbggrr form.
    */
    virtual DWORD GetRGB(const wchar_t* name, DWORD defValue) = 0;

    //! Set a field value as COLORREF type.
    /*!
        \param name the field name.
        \param value the new field value as 0x00bbggrr form.
        \return true if the field value changed.
    */
    virtual bool SetRGB(const wchar_t* name, DWORD value) = 0;

    //! Get a field value as CMYK color type.
    /*!
        \param[in] name the field name.
        \param[out] c fills C value if successful.
        \param[out] m fills M value if successful.
        \param[out] y fills Y value if successful.
        \param[out] k fills K value if successful.
        \return true if successful.
    */
    virtual bool GetCMYK(const wchar_t* name, WORD& c, WORD& m, WORD& y, WORD& k) = 0;

    //! Set a field value as CMYK color type.
    /*!
        \param name the field name.
        \param c the C component of the CMYK value.
        \param m the M component of the CMYK value.
        \param y the Y component of the CMYK value.
        \param k the K component of the CMYK value.
        \return true if the field value changed.
    */
    virtual bool SetCMYK(const wchar_t* name, WORD c, WORD m, WORD y, WORD k) = 0;

    //! Get a field value as date type.
    /*!
        \param[in] name the field name.
        \param[out] year fills year value (1980-2099) if successful.
        \param[out] month fills month value (0-12) if successful.
        \param[out] day fills day value (0-31) if successful.
        \return true if successful.
    */
    virtual bool GetDate(const wchar_t* name, int& year, int& month, int& day) = 0;

    //! Set a field value as date type.
    /*!
        \param name the field name.
        \param year year value (1980-2099)
        \param month month value (0-12)
        \param day day value (0-31)
        \return true if the field value changed.
    */
    virtual bool SetDate(const wchar_t* name, int year, int month, int day) = 0;

    //! Get a field value as date time type.
    /*!
        \param[in] name the field name.
        \param[out] year fills year value (1980-2099) if successful.
        \param[out] month fills month value (0-12) if successful.
        \param[out] day fills day value (0-31) if successful.
        \param[out] hour fills hour value (0-24) if successful.
        \param[out] minute fills minute value (0-60) if successful.
        \param[out] second fills second value (0-60) if successful.
        \return true if successful.
    */
    virtual bool GetDateTime(const wchar_t* name, int& year, int& month, int& day,
        int& hour, int& minute, int& second) = 0;

    //! Set a field value as date time type.
    /*!
        \param name the field name.
        \param year year value (1980-2099)
        \param month month value (0-12)
        \param day day value (0-31)
        \param hour hour value (0-24)
        \param minute minute value (0-60)
        \param second second value (0-60)
        \return true if the field value changed.
    */
    virtual bool SetDateTime(const wchar_t* name, int year, int month, int day,
        int hour, int minute, int second) = 0;

    //! Get a field value as double array type.
    /*!
        \param[in] name the field name.
        \param[out] items fills values (limit to count) if successful.
        \param[in] count the max element count of items.
        \return the count of elements read (0 to count).
    */
    virtual long GetDoubleArray(const wchar_t* name, double* items, long count) = 0;

    //! Set a field value as double array type.
    /*!
        \param name the field name.
        \param items the values to save.
        \param count the element count of items.
        \return true if successful.
    */
    virtual bool SetDoubleArray(const wchar_t* name, const double* items, long count) = 0;

    //! Get a field value as integer array type.
    /*!
        \param[in] name the field name.
        \param[out] items fills values (limit to count) if successful.
        \param[in] count the max element count of items.
        \return the count of elements read (0 to count).
    */
    virtual long GetIntArray(const wchar_t* name, long* items, long count) = 0;

    //! Set a field value as integer array type.
    /*!
        \param name the field name.
        \param items the values to save.
        \param count the element count of items.
        \return true if successful.
    */
    virtual bool SetIntArray(const wchar_t* name, const long* items, long count) = 0;

    //! Get a field value as buffer type.
    /*!
        \param[in] name the field name.
        \param[out] buf fills (limit to size bytes) if successful.
        \param[in] size buffer size in bytes.
        \return bytes read (0 to count).
    */
    virtual long GetBinary(const wchar_t* name, void* buf, long size) = 0;

    //! Set a field value as buffer type.
    /*!
        \param name the field name.
        \param buf the buffer to save.
        \param size buffer size in bytes.
        \return true if successful.
    */
    virtual bool SetBinary(const wchar_t* name, const void* buf, long size) = 0;
};

#endif // X3_XML_ICONFIGSECTION_H_
