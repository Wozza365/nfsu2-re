// PROFILE: game
#include <stdarg.h>
int FormatWithSinglePlaceholderPtrTimed(char *dest, char *format, va_list va);
// FUNCTION: 0x004400D0
int FormatWithSinglePlaceholderValueTimed(char *dest, char *format, ...)
{
	va_list va;
	va_start(va, format);
	return FormatWithSinglePlaceholderPtrTimed(dest, format, va);
}
