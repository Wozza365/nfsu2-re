// PROFILE: game
// ShowUIElementAndChildrenByHash, 25 bytes
// yugecin's prototype: void __cdecl ShowUIElementAndChildrenByHash(char *fngName, unsigned int hash);
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

// FUNCTION: 0x00495520
void ShowUIElementAndChildrenByHash(const char *fngName, unsigned int hash)
{
	ShowNullableUIElementAndChildren(FindUIElementByHash(fngName, hash));
}
