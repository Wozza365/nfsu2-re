// PROFILE: game
// HideUIElementAndChildrenByHash, 25 bytes
// yugecin's prototype: void __cdecl HideUIElementAndChildrenByHash(char *fngName, unsigned int hash);
struct UIElement;
struct UILabel;
struct UIElementType1;
unsigned int cihash(const char *str);
UIElement *FindUIElementByHash(const char *fngName, unsigned int hash);
UILabel *FindUILabelByHash(const char *fngName, unsigned int hash);
UIElementType1 *FindUIElementType1ByHash(const char *fngName, unsigned int hash);
int SetUILabelLanguageString(UILabel *label, unsigned int languageString);
void HideNullableUIElementAndChildren(UIElement *uielement);
void ShowNullableUIElementAndChildren(UIElement *uielement);

// FUNCTION: 0x004954E0
void HideUIElementAndChildrenByHash(const char *fngName, unsigned int hash)
{
	HideNullableUIElementAndChildren(FindUIElementByHash(fngName, hash));
}
