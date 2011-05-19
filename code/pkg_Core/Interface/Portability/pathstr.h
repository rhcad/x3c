// Included by portimpl.h to implement path functions.

#ifndef X3_PORTABILITY_PATHSTR_IMPL_H
#define X3_PORTABILITY_PATHSTR_IMPL_H

char* PathFindFileNameA(const char* path)
{
    return NULL;
}

wchar_t* PathFindFileNameW(const wchar_t* path)
{
    return NULL;
}

bool PathIsRelativeW(const wchar_t* path)
{
    return false;
}

void PathStripPathW(wchar_t* path)
{
}

void PathRemoveFileSpecW(wchar_t* path)
{
}

void PathRemoveExtensionW(wchar_t* path)
{
}

void PathRemoveBackslashW(wchar_t* path)
{
}

void PathAppendW(wchar_t* path, const wchar_t* more)
{
}

wchar_t* PathAddBackslashW(wchar_t* path)
{
    return NULL;
}

void PathRenameExtensionW(wchar_t* path, const wchar_t* more)
{
}

#endif // X3_PORTABILITY_PATHSTR_IMPL_H
