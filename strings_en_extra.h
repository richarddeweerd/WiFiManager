#ifndef _WM_STRINGS_EXTRA_H_
#define _WM_STRINGS_EXTRA_H_

#ifndef WIFI_MANAGER_MAX_OPTIONS
#define WIFI_MANAGER_MAX_OPTIONS 5  // params will autoincrement and realloc by this amount when max is reached
#endif

const char HTTP_FORM_PARAM_PASS[] PROGMEM = "<br/><input type=\"password\" id='{i}' name='{n}' maxlength='{l}' {c}>\n";
const char HTTP_FORM_PARAM_CHECKBOX[] PROGMEM = "<br/><input type=\"checkbox\" id='{i}' name='{n}' value='true' {C} {c}>";
const char HTTP_FORM_PARAM_SELECT[] PROGMEM = "<br/> <select id='{i}' name='{n}'>{o}</select>";
const char HTTP_FORM_PARAM_SELECT_OPTION[] PROGMEM = "<option value='{v}'{s}>{l}</option>";
const char HTTP_FORM_PARAM_RADIO[] PROGMEM = "<br/><input type='radio' id='{i}' name='{n}' value='{ov}'{C}><label for='{on}'>{ol}</label>";
const char HTTP_FORM_PARAM_CHECKED[] PROGMEM = " checked";
const char HTTP_FORM_PARAM_SELECTED[] PROGMEM = " selected";
const char HTTP_FORM_PARAM_SPACER[] PROGMEM = "<br/> <hr>";

const char T_o[] PROGMEM = "{o}";    // @token o
const char T_s[] PROGMEM = "{s}";    // @token s
const char T_C[] PROGMEM = "{C}";    // @token C
const char T_ov[] PROGMEM = "{ov}";  // @token ov
const char T_on[] PROGMEM = "{on}";  // @token on
const char T_ol[] PROGMEM = "{ol}";  // @token on

#endif