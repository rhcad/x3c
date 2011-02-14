#ifndef _XMLDOM_HELPERS_H
#define _XMLDOM_HELPERS_H

#pragma pack(push, 8)

#include <comdef.h>

namespace XML {

struct __declspec(uuid("2933bf8f-7b36-11d2-b20e-00c04f983e60")) IXMLDOMImplementation;
struct __declspec(uuid("2933bf80-7b36-11d2-b20e-00c04f983e60")) IXMLDOMNode;
struct __declspec(uuid("2933bf82-7b36-11d2-b20e-00c04f983e60")) IXMLDOMNodeList;
struct __declspec(uuid("2933bf83-7b36-11d2-b20e-00c04f983e60")) IXMLDOMNamedNodeMap;
struct __declspec(uuid("2933bf81-7b36-11d2-b20e-00c04f983e60")) IXMLDOMDocument;
struct __declspec(uuid("2933bf8b-7b36-11d2-b20e-00c04f983e60")) IXMLDOMDocumentType;
struct __declspec(uuid("2933bf86-7b36-11d2-b20e-00c04f983e60")) IXMLDOMElement;
struct __declspec(uuid("2933bf85-7b36-11d2-b20e-00c04f983e60")) IXMLDOMAttribute;
struct __declspec(uuid("3efaa413-272f-11d2-836f-0000f87a7782")) IXMLDOMDocumentFragment;
struct __declspec(uuid("2933bf87-7b36-11d2-b20e-00c04f983e60")) IXMLDOMText;
struct __declspec(uuid("2933bf8a-7b36-11d2-b20e-00c04f983e60")) IXMLDOMCDATASection;
struct __declspec(uuid("2933bf88-7b36-11d2-b20e-00c04f983e60")) IXMLDOMComment;
struct __declspec(uuid("2933bf89-7b36-11d2-b20e-00c04f983e60")) IXMLDOMProcessingInstruction;
struct __declspec(uuid("2933bf8e-7b36-11d2-b20e-00c04f983e60")) IXMLDOMEntityReference;
struct __declspec(uuid("3efaa426-272f-11d2-836f-0000f87a7782")) IXMLDOMParseError;
struct __declspec(uuid("2933bf8c-7b36-11d2-b20e-00c04f983e60")) IXMLDOMNotation;
struct __declspec(uuid("2933bf8d-7b36-11d2-b20e-00c04f983e60")) IXMLDOMEntity;
struct __declspec(uuid("3efaa425-272f-11d2-836f-0000f87a7782")) IXTLRuntime;
struct __declspec(uuid("3efaa427-272f-11d2-836f-0000f87a7782")) IXMLDOMDocumentEvents;
struct __declspec(uuid("65725580-9b5d-11d0-9bfe-00c04fc99c8e")) IXMLElementCollection;
struct __declspec(uuid("f52e2b61-18a1-11d1-b105-00805f49916b")) IXMLDocument;
struct __declspec(uuid("3f7f31ac-e15f-11d0-9c25-00c04fc99c8e")) IXMLElement;
struct __declspec(uuid("2b8de2fe-8d2d-11d1-b2fc-00c04fd915a9")) IXMLDocument2;
struct __declspec(uuid("2b8de2ff-8d2d-11d1-b2fc-00c04fd915a9")) IXMLElement2;
struct __declspec(uuid("d4d4a0fc-3b73-11d1-b2b4-00c04fb92596")) IXMLAttribute;
struct __declspec(uuid("948c5ad3-c58d-11d0-9c0b-00c04fc99c8e")) IXMLError;

_COM_SMARTPTR_TYPEDEF(IXMLDOMImplementation, __uuidof(IXMLDOMImplementation));
_COM_SMARTPTR_TYPEDEF(IXMLDOMNode, __uuidof(IXMLDOMNode));
_COM_SMARTPTR_TYPEDEF(IXMLDOMNodeList, __uuidof(IXMLDOMNodeList));
_COM_SMARTPTR_TYPEDEF(IXMLDOMNamedNodeMap, __uuidof(IXMLDOMNamedNodeMap));
_COM_SMARTPTR_TYPEDEF(IXMLDOMDocument, __uuidof(IXMLDOMDocument));
_COM_SMARTPTR_TYPEDEF(IXMLDOMDocumentType, __uuidof(IXMLDOMDocumentType));
_COM_SMARTPTR_TYPEDEF(IXMLDOMElement, __uuidof(IXMLDOMElement));
_COM_SMARTPTR_TYPEDEF(IXMLDOMAttribute, __uuidof(IXMLDOMAttribute));
_COM_SMARTPTR_TYPEDEF(IXMLDOMDocumentFragment, __uuidof(IXMLDOMDocumentFragment));
_COM_SMARTPTR_TYPEDEF(IXMLDOMText, __uuidof(IXMLDOMText));
_COM_SMARTPTR_TYPEDEF(IXMLDOMCDATASection, __uuidof(IXMLDOMCDATASection));
_COM_SMARTPTR_TYPEDEF(IXMLDOMProcessingInstruction, __uuidof(IXMLDOMProcessingInstruction));
_COM_SMARTPTR_TYPEDEF(IXMLDOMEntityReference, __uuidof(IXMLDOMEntityReference));
_COM_SMARTPTR_TYPEDEF(IXMLDOMParseError, __uuidof(IXMLDOMParseError));
_COM_SMARTPTR_TYPEDEF(IXMLDOMNotation, __uuidof(IXMLDOMNotation));
_COM_SMARTPTR_TYPEDEF(IXMLDOMEntity, __uuidof(IXMLDOMEntity));
_COM_SMARTPTR_TYPEDEF(IXTLRuntime, __uuidof(IXTLRuntime));
_COM_SMARTPTR_TYPEDEF(IXMLDOMDocumentEvents, __uuidof(IDispatch));
_COM_SMARTPTR_TYPEDEF(IXMLElementCollection, __uuidof(IXMLElementCollection));
_COM_SMARTPTR_TYPEDEF(IXMLDocument, __uuidof(IXMLDocument));
_COM_SMARTPTR_TYPEDEF(IXMLElement, __uuidof(IXMLElement));
_COM_SMARTPTR_TYPEDEF(IXMLDocument2, __uuidof(IXMLDocument2));
_COM_SMARTPTR_TYPEDEF(IXMLElement2, __uuidof(IXMLElement2));
_COM_SMARTPTR_TYPEDEF(IXMLAttribute, __uuidof(IXMLAttribute));
_COM_SMARTPTR_TYPEDEF(IXMLError, __uuidof(IXMLError));

enum tagXMLEMEM_TYPE
{
	XMLELEMTYPE_ELEMENT = 0,
	XMLELEMTYPE_TEXT = 1,
	XMLELEMTYPE_COMMENT = 2,
	XMLELEMTYPE_DOCUMENT = 3,
	XMLELEMTYPE_DTD = 4,
	XMLELEMTYPE_PI = 5,
	XMLELEMTYPE_OTHER = 6
};

enum tagXMLDOMNodeType
{
	NODE_INVALID = 0,
	NODE_ELEMENT = 1,
	NODE_ATTRIBUTE = 2,
	NODE_TEXT = 3,
	NODE_CDATA_SECTION = 4,
	NODE_ENTITY_REFERENCE = 5,
	NODE_ENTITY = 6,
	NODE_PROCESSING_INSTRUCTION = 7,
	NODE_COMMENT = 8,
	NODE_DOCUMENT = 9,
	NODE_DOCUMENT_TYPE = 10,
	NODE_DOCUMENT_FRAGMENT = 11,
	NODE_NOTATION = 12
};

typedef enum tagXMLEMEM_TYPE _XMLELEM_TYPE;
typedef enum tagXMLDOMNodeType _XMLDOMNodeType;

struct _xml_error;

//
// Type library items
//

struct __declspec(uuid("2933bf8f-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMImplementation : IDispatch
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall hasFeature (
		BSTR feature,
		BSTR version,
		VARIANT_BOOL * hasFeature ) = 0;
};

struct __declspec(uuid("2933bf80-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMNode : IDispatch
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_nodeName (
		BSTR * name ) = 0;
	virtual HRESULT __stdcall get_nodeValue (
		VARIANT * value ) = 0;
	virtual HRESULT __stdcall put_nodeValue (
		VARIANT value ) = 0;
	virtual HRESULT __stdcall get_nodeType (
		_XMLDOMNodeType * type ) = 0;
	virtual HRESULT __stdcall get_parentNode (
		struct IXMLDOMNode * * parent ) = 0;
	virtual HRESULT __stdcall get_childNodes (
		struct IXMLDOMNodeList * * childList ) = 0;
	virtual HRESULT __stdcall get_firstChild (
		struct IXMLDOMNode * * firstChild ) = 0;
	virtual HRESULT __stdcall get_lastChild (
		struct IXMLDOMNode * * lastChild ) = 0;
	virtual HRESULT __stdcall get_previousSibling (
		struct IXMLDOMNode * * previousSibling ) = 0;
	virtual HRESULT __stdcall get_nextSibling (
		struct IXMLDOMNode * * nextSibling ) = 0;
	virtual HRESULT __stdcall get_attributes (
		struct IXMLDOMNamedNodeMap * * attributeMap ) = 0;
	virtual HRESULT __stdcall insertBefore (
		struct IXMLDOMNode * newChild,
		VARIANT refChild,
		struct IXMLDOMNode * * outNewChild ) = 0;
	virtual HRESULT __stdcall replaceChild (
		struct IXMLDOMNode * newChild,
		struct IXMLDOMNode * oldChild,
		struct IXMLDOMNode * * outOldChild ) = 0;
	virtual HRESULT __stdcall removeChild (
		struct IXMLDOMNode * childNode,
		struct IXMLDOMNode * * oldChild ) = 0;
	virtual HRESULT __stdcall appendChild (
		struct IXMLDOMNode * newChild,
		struct IXMLDOMNode * * outNewChild ) = 0;
	virtual HRESULT __stdcall hasChildNodes (
		VARIANT_BOOL * hasChild ) = 0;
	virtual HRESULT __stdcall get_ownerDocument (
		struct IXMLDOMDocument * * XTPXMLDOMDocument ) = 0;
	virtual HRESULT __stdcall cloneNode (
		VARIANT_BOOL deep,
		struct IXMLDOMNode * * cloneRoot ) = 0;
	virtual HRESULT __stdcall get_nodeTypeString (
		BSTR * nodeType ) = 0;
	virtual HRESULT __stdcall get_text (
		BSTR * text ) = 0;
	virtual HRESULT __stdcall put_text (
		BSTR text ) = 0;
	virtual HRESULT __stdcall get_specified (
		VARIANT_BOOL * isSpecified ) = 0;
	virtual HRESULT __stdcall get_definition (
		struct IXMLDOMNode * * definitionNode ) = 0;
	virtual HRESULT __stdcall get_nodeTypedValue (
		VARIANT * typedValue ) = 0;
	virtual HRESULT __stdcall put_nodeTypedValue (
		VARIANT typedValue ) = 0;
	virtual HRESULT __stdcall get_dataType (
		VARIANT * dataTypeName ) = 0;
	virtual HRESULT __stdcall put_dataType (
		BSTR dataTypeName ) = 0;
	virtual HRESULT __stdcall get_xml (
		BSTR * xmlString ) = 0;
	virtual HRESULT __stdcall transformNode (
		struct IXMLDOMNode * stylesheet,
		BSTR * xmlString ) = 0;
	virtual HRESULT __stdcall selectNodes (
		BSTR queryString,
		struct IXMLDOMNodeList * * resultList ) = 0;
	virtual HRESULT __stdcall selectSingleNode (
		BSTR queryString,
		struct IXMLDOMNode * * resultNode ) = 0;
	virtual HRESULT __stdcall get_parsed (
		VARIANT_BOOL * isParsed ) = 0;
	virtual HRESULT __stdcall get_namespaceURI (
		BSTR * namespaceURI ) = 0;
	virtual HRESULT __stdcall get_prefix (
		BSTR * prefixString ) = 0;
	virtual HRESULT __stdcall get_baseName (
		BSTR * nameString ) = 0;
	virtual HRESULT __stdcall transformNodeToObject (
		struct IXMLDOMNode * stylesheet,
		VARIANT outputObject ) = 0;
};

struct __declspec(uuid("2933bf82-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMNodeList : IDispatch
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_item (
		long index,
		struct IXMLDOMNode * * listItem ) = 0;
	virtual HRESULT __stdcall get_length (
		long * listLength ) = 0;
	virtual HRESULT __stdcall nextNode (
		struct IXMLDOMNode * * nextItem ) = 0;
	virtual HRESULT __stdcall reset ( ) = 0;
	virtual HRESULT __stdcall get__newEnum (
		IUnknown * * ppUnk ) = 0;
};

struct __declspec(uuid("2933bf83-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMNamedNodeMap : IDispatch
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall getNamedItem (
		BSTR name,
		struct IXMLDOMNode * * namedItem ) = 0;
	virtual HRESULT __stdcall setNamedItem (
		struct IXMLDOMNode * newItem,
		struct IXMLDOMNode * * nameItem ) = 0;
	virtual HRESULT __stdcall removeNamedItem (
		BSTR name,
		struct IXMLDOMNode * * namedItem ) = 0;
	virtual HRESULT __stdcall get_item (
		long index,
		struct IXMLDOMNode * * listItem ) = 0;
	virtual HRESULT __stdcall get_length (
		long * listLength ) = 0;
	virtual HRESULT __stdcall getQualifiedItem (
		BSTR baseName,
		BSTR namespaceURI,
		struct IXMLDOMNode * * qualifiedItem ) = 0;
	virtual HRESULT __stdcall removeQualifiedItem (
		BSTR baseName,
		BSTR namespaceURI,
		struct IXMLDOMNode * * qualifiedItem ) = 0;
	virtual HRESULT __stdcall nextNode (
		struct IXMLDOMNode * * nextItem ) = 0;
	virtual HRESULT __stdcall reset ( ) = 0;
	virtual HRESULT __stdcall get__newEnum (
		IUnknown * * ppUnk ) = 0;
};

struct __declspec(uuid("2933bf81-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMDocument : IXMLDOMNode
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_doctype (
		struct IXMLDOMDocumentType * * documentType ) = 0;
	virtual HRESULT __stdcall get_implementation (
		struct IXMLDOMImplementation * * impl ) = 0;
	virtual HRESULT __stdcall get_documentElement (
		struct IXMLDOMElement * * XMLDOMElement ) = 0;
	virtual HRESULT __stdcall putref_documentElement (
		struct IXMLDOMElement * XMLDOMElement ) = 0;
	virtual HRESULT __stdcall createElement (
		BSTR tagName,
		struct IXMLDOMElement * * element ) = 0;
	virtual HRESULT __stdcall createDocumentFragment (
		struct IXMLDOMDocumentFragment * * docFrag ) = 0;
	virtual HRESULT __stdcall createTextNode (
		BSTR data,
		struct IXMLDOMText * * text ) = 0;
	virtual HRESULT __stdcall createComment (
		BSTR data,
		struct IXMLDOMComment * * comment ) = 0;
	virtual HRESULT __stdcall createCDATASection (
		BSTR data,
		struct IXMLDOMCDATASection * * cdata ) = 0;
	virtual HRESULT __stdcall createProcessingInstruction (
		BSTR target,
		BSTR data,
		struct IXMLDOMProcessingInstruction * * pi ) = 0;
	virtual HRESULT __stdcall createAttribute (
		BSTR name,
		struct IXMLDOMAttribute * * attribute ) = 0;
	virtual HRESULT __stdcall createEntityReference (
		BSTR name,
		struct IXMLDOMEntityReference * * entityRef ) = 0;
	virtual HRESULT __stdcall getElementsByTagName (
		BSTR tagName,
		struct IXMLDOMNodeList * * resultList ) = 0;
	virtual HRESULT __stdcall createNode (
		VARIANT type,
		BSTR name,
		BSTR namespaceURI,
		struct IXMLDOMNode * * node ) = 0;
	virtual HRESULT __stdcall nodeFromID (
		BSTR idString,
		struct IXMLDOMNode * * node ) = 0;
	virtual HRESULT __stdcall load (
		VARIANT xmlSource,
		VARIANT_BOOL * isSuccessful ) = 0;
	virtual HRESULT __stdcall get_readyState (
		long * value ) = 0;
	virtual HRESULT __stdcall get_parseError (
		struct IXMLDOMParseError * * errorObj ) = 0;
	virtual HRESULT __stdcall get_url (
		BSTR * urlString ) = 0;
	virtual HRESULT __stdcall get_async (
		VARIANT_BOOL * isAsync ) = 0;
	virtual HRESULT __stdcall put_async (
		VARIANT_BOOL isAsync ) = 0;
	virtual HRESULT __stdcall abort ( ) = 0;
	virtual HRESULT __stdcall loadXML (
		BSTR bstrXML,
		VARIANT_BOOL * isSuccessful ) = 0;
	virtual HRESULT __stdcall save (
		VARIANT desination ) = 0;
	virtual HRESULT __stdcall get_validateOnParse (
		VARIANT_BOOL * isValidating ) = 0;
	virtual HRESULT __stdcall put_validateOnParse (
		VARIANT_BOOL isValidating ) = 0;
	virtual HRESULT __stdcall get_resolveExternals (
		VARIANT_BOOL * isResolving ) = 0;
	virtual HRESULT __stdcall put_resolveExternals (
		VARIANT_BOOL isResolving ) = 0;
	virtual HRESULT __stdcall get_preserveWhiteSpace (
		VARIANT_BOOL * isPreserving ) = 0;
	virtual HRESULT __stdcall put_preserveWhiteSpace (
		VARIANT_BOOL isPreserving ) = 0;
	virtual HRESULT __stdcall put_onreadystatechange (
		VARIANT _arg1 ) = 0;
	virtual HRESULT __stdcall put_ondataavailable (
		VARIANT _arg1 ) = 0;
	virtual HRESULT __stdcall put_ontransformnode (
		VARIANT _arg1 ) = 0;
};

struct __declspec(uuid("2933bf8b-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMDocumentType : IXMLDOMNode
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_name (
		BSTR * rootName ) = 0;
	virtual HRESULT __stdcall get_entities (
		struct IXMLDOMNamedNodeMap * * entityMap ) = 0;
	virtual HRESULT __stdcall get_notations (
		struct IXMLDOMNamedNodeMap * * notationMap ) = 0;
};

struct __declspec(uuid("2933bf86-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMElement : IXMLDOMNode
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_tagName (
		BSTR * tagName ) = 0;
	virtual HRESULT __stdcall getAttribute (
		BSTR name,
		VARIANT * value ) = 0;
	virtual HRESULT __stdcall setAttribute (
		BSTR name,
		VARIANT value ) = 0;
	virtual HRESULT __stdcall removeAttribute (
		BSTR name ) = 0;
	virtual HRESULT __stdcall getAttributeNode (
		BSTR name,
		struct IXMLDOMAttribute * * attributeNode ) = 0;
	virtual HRESULT __stdcall setAttributeNode (
		struct IXMLDOMAttribute * XMLDOMAttribute,
		struct IXMLDOMAttribute * * attributeNode ) = 0;
	virtual HRESULT __stdcall removeAttributeNode (
		struct IXMLDOMAttribute * XMLDOMAttribute,
		struct IXMLDOMAttribute * * attributeNode ) = 0;
	virtual HRESULT __stdcall getElementsByTagName (
		BSTR tagName,
		struct IXMLDOMNodeList * * resultList ) = 0;
	virtual HRESULT __stdcall normalize ( ) = 0;
};

struct __declspec(uuid("2933bf85-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMAttribute : IXMLDOMNode
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_name (
		BSTR * attributeName ) = 0;
	virtual HRESULT __stdcall get_value (
		VARIANT * attributeValue ) = 0;
	virtual HRESULT __stdcall put_value (
		VARIANT attributeValue ) = 0;
};

struct __declspec(uuid("3efaa413-272f-11d2-836f-0000f87a7782"))
IXMLDOMDocumentFragment : IXMLDOMNode
{};

struct __declspec(uuid("2933bf84-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMCharacterData : IXMLDOMNode
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_data (
		BSTR * data ) = 0;
	virtual HRESULT __stdcall put_data (
		BSTR data ) = 0;
	virtual HRESULT __stdcall get_length (
		long * dataLength ) = 0;
	virtual HRESULT __stdcall substringData (
		long offset,
		long count,
		BSTR * data ) = 0;
	virtual HRESULT __stdcall appendData (
		BSTR data ) = 0;
	virtual HRESULT __stdcall insertData (
		long offset,
		BSTR data ) = 0;
	virtual HRESULT __stdcall deleteData (
		long offset,
		long count ) = 0;
	virtual HRESULT __stdcall replaceData (
		long offset,
		long count,
		BSTR data ) = 0;
};

struct __declspec(uuid("2933bf88-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMComment : IXMLDOMCharacterData
{};


struct __declspec(uuid("2933bf89-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMProcessingInstruction : IXMLDOMNode
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_target (
		BSTR * name ) = 0;
	virtual HRESULT __stdcall get_data (
		BSTR * value ) = 0;
	virtual HRESULT __stdcall put_data (
		BSTR value ) = 0;
};

struct __declspec(uuid("2933bf8e-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMEntityReference : IXMLDOMNode
{};

struct __declspec(uuid("3efaa426-272f-11d2-836f-0000f87a7782"))
IXMLDOMParseError : IDispatch
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_errorCode (
		long * errorCode ) = 0;
	virtual HRESULT __stdcall get_url (
		BSTR * urlString ) = 0;
	virtual HRESULT __stdcall get_reason (
		BSTR * reasonString ) = 0;
	virtual HRESULT __stdcall get_srcText (
		BSTR * sourceString ) = 0;
	virtual HRESULT __stdcall get_line (
		long * lineNumber ) = 0;
	virtual HRESULT __stdcall get_linepos (
		long * linePosition ) = 0;
	virtual HRESULT __stdcall get_filepos (
		long * filePosition ) = 0;
};

struct __declspec(uuid("2933bf8c-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMNotation : IXMLDOMNode
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_publicId (
		VARIANT * publicId ) = 0;
	virtual HRESULT __stdcall get_systemId (
		VARIANT * systemId ) = 0;
};

struct __declspec(uuid("2933bf8d-7b36-11d2-b20e-00c04f983e60"))
IXMLDOMEntity : IXMLDOMNode
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_publicId (
		VARIANT * publicId ) = 0;
	virtual HRESULT __stdcall get_systemId (
		VARIANT * systemId ) = 0;
	virtual HRESULT __stdcall get_notationName (
		BSTR * name ) = 0;
};

struct __declspec(uuid("3efaa425-272f-11d2-836f-0000f87a7782"))
IXTLRuntime : IXMLDOMNode
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall uniqueID (
		struct IXMLDOMNode * pNode,
		long * pID ) = 0;
	virtual HRESULT __stdcall depth (
		struct IXMLDOMNode * pNode,
		long * pDepth ) = 0;
	virtual HRESULT __stdcall childNumber (
		struct IXMLDOMNode * pNode,
		long * pNumber ) = 0;
	virtual HRESULT __stdcall ancestorChildNumber (
		BSTR bstrNodeName,
		struct IXMLDOMNode * pNode,
		long * pNumber ) = 0;
	virtual HRESULT __stdcall absoluteChildNumber (
		struct IXMLDOMNode * pNode,
		long * pNumber ) = 0;
	virtual HRESULT __stdcall formatIndex (
		long lIndex,
		BSTR bstrFormat,
		BSTR * pbstrFormattedString ) = 0;
	virtual HRESULT __stdcall formatNumber (
		double dblNumber,
		BSTR bstrFormat,
		BSTR * pbstrFormattedString ) = 0;
	virtual HRESULT __stdcall formatDate (
		VARIANT varDate,
		BSTR bstrFormat,
		VARIANT varDestLocale,
		BSTR * pbstrFormattedString ) = 0;
	virtual HRESULT __stdcall formatTime (
		VARIANT varTime,
		BSTR bstrFormat,
		VARIANT varDestLocale,
		BSTR * pbstrFormattedString ) = 0;
};

struct __declspec(uuid("65725580-9b5d-11d0-9bfe-00c04fc99c8e"))
IXMLElementCollection : IDispatch
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall put_length (
		long p ) = 0;
	virtual HRESULT __stdcall get_length (
		long * p ) = 0;
	virtual HRESULT __stdcall get__newEnum (
		IUnknown * * ppUnk ) = 0;
	virtual HRESULT __stdcall item (
		VARIANT var1,
		VARIANT var2,
		IDispatch * * ppDisp ) = 0;
};

struct __declspec(uuid("f52e2b61-18a1-11d1-b105-00805f49916b"))
IXMLDocument : IDispatch
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_root (
		struct IXMLElement * * p ) = 0;
	virtual HRESULT __stdcall get_fileSize (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_fileModifiedDate (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_fileUpdatedDate (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_url (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall put_url (
		BSTR p ) = 0;
	virtual HRESULT __stdcall get_mimeType (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_readyState (
		long * pl ) = 0;
	virtual HRESULT __stdcall get_charset (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall put_charset (
		BSTR p ) = 0;
	virtual HRESULT __stdcall get_version (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_doctype (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_dtdURL (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall createElement (
		VARIANT vType,
		VARIANT var1,
		struct IXMLElement * * ppElem ) = 0;
};

struct __declspec(uuid("3f7f31ac-e15f-11d0-9c25-00c04fc99c8e"))
IXMLElement : IDispatch
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_tagName (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall put_tagName (
		BSTR p ) = 0;
	virtual HRESULT __stdcall get_parent (
		struct IXMLElement * * ppParent ) = 0;
	virtual HRESULT __stdcall setAttribute (
		BSTR strPropertyName,
		VARIANT PropertyValue ) = 0;
	virtual HRESULT __stdcall getAttribute (
		BSTR strPropertyName,
		VARIANT * PropertyValue ) = 0;
	virtual HRESULT __stdcall removeAttribute (
		BSTR strPropertyName ) = 0;
	virtual HRESULT __stdcall get_children (
		struct IXMLElementCollection * * pp ) = 0;
	virtual HRESULT __stdcall get_type (
		long * plType ) = 0;
	virtual HRESULT __stdcall get_text (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall put_text (
		BSTR p ) = 0;
	virtual HRESULT __stdcall addChild (
		struct IXMLElement * pChildElem,
		long lIndex,
		long lReserved ) = 0;
	virtual HRESULT __stdcall removeChild (
		struct IXMLElement * pChildElem ) = 0;
};

struct __declspec(uuid("2b8de2fe-8d2d-11d1-b2fc-00c04fd915a9"))
IXMLDocument2 : IDispatch
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_root (
		struct IXMLElement2 * * p ) = 0;
	virtual HRESULT __stdcall get_fileSize (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_fileModifiedDate (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_fileUpdatedDate (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_url (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall put_url (
		BSTR p ) = 0;
	virtual HRESULT __stdcall get_mimeType (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_readyState (
		long * pl ) = 0;
	virtual HRESULT __stdcall get_charset (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall put_charset (
		BSTR p ) = 0;
	virtual HRESULT __stdcall get_version (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_doctype (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall get_dtdURL (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall createElement (
		VARIANT vType,
		VARIANT var1,
		struct IXMLElement2 * * ppElem ) = 0;
	virtual HRESULT __stdcall get_async (
		VARIANT_BOOL * pf ) = 0;
	virtual HRESULT __stdcall put_async (
		VARIANT_BOOL pf ) = 0;
};

struct __declspec(uuid("2b8de2ff-8d2d-11d1-b2fc-00c04fd915a9"))
IXMLElement2 : IDispatch
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_tagName (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall put_tagName (
		BSTR p ) = 0;
	virtual HRESULT __stdcall get_parent (
		struct IXMLElement2 * * ppParent ) = 0;
	virtual HRESULT __stdcall setAttribute (
		BSTR strPropertyName,
		VARIANT PropertyValue ) = 0;
	virtual HRESULT __stdcall getAttribute (
		BSTR strPropertyName,
		VARIANT * PropertyValue ) = 0;
	virtual HRESULT __stdcall removeAttribute (
		BSTR strPropertyName ) = 0;
	virtual HRESULT __stdcall get_children (
		struct IXMLElementCollection * * pp ) = 0;
	virtual HRESULT __stdcall get_type (
		long * plType ) = 0;
	virtual HRESULT __stdcall get_text (
		BSTR * p ) = 0;
	virtual HRESULT __stdcall put_text (
		BSTR p ) = 0;
	virtual HRESULT __stdcall addChild (
		struct IXMLElement2 * pChildElem,
		long lIndex,
		long lReserved ) = 0;
	virtual HRESULT __stdcall removeChild (
		struct IXMLElement2 * pChildElem ) = 0;
	virtual HRESULT __stdcall get_attributes (
		struct IXMLElementCollection * * pp ) = 0;
};

struct __declspec(uuid("d4d4a0fc-3b73-11d1-b2b4-00c04fb92596"))
IXMLAttribute : IDispatch
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall get_name (
		BSTR * n ) = 0;
	virtual HRESULT __stdcall get_value (
		BSTR * v ) = 0;
};

struct __declspec(uuid("948c5ad3-c58d-11d0-9c0b-00c04fc99c8e"))
IXMLError : IUnknown
{
	//
	// Raw methods provided by interface
	//

	virtual HRESULT __stdcall GetErrorInfo (
		struct _xml_error * pErrorReturn ) = 0;
};

struct _xml_error
{
	unsigned int _nLine;
	BSTR _pchBuf;
	unsigned int _cchBuf;
	unsigned int _ich;
	BSTR _pszFound;
	BSTR _pszExpected;
	unsigned long _reserved1;
	unsigned long _reserved2;
};

struct __declspec(uuid("cfc399af-d876-11d0-9c10-00c04fc99c8e"))
XMLDocument;
	// [ default ] interface IXMLDocument2

}

#pragma pack(pop)

typedef XML::IXMLDOMNodePtr         XMLDOMNodePtr;
typedef XML::IXMLDOMDocumentPtr     XMLDOMDocumentPtr;
typedef XML::IXMLDOMElementPtr      XMLDOMElementPtr;
typedef XML::IXMLDOMNamedNodeMapPtr XMLDOMNamedNodeMapPtr;
typedef XML::IXMLDOMProcessingInstructionPtr XMLDOMProcessingInstructionPtr;
typedef XML::IXMLDOMComment         XMLDOMComment;
typedef XML::IXMLDOMNodeListPtr     XMLDOMNodeListPtr;
typedef XML::IXMLDOMAttributePtr    XMLDOMAttributePtr;
typedef XML::_XMLDOMNodeType        XMLDOMNodeType;
typedef XML::_XMLELEM_TYPE          XMLDOM_ELEMTYPE;

#endif // _XMLDOM_HELPERS_H
