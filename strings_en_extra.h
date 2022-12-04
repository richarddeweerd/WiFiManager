#ifndef _WM_STRINGS_EXTRA_H_
#define _WM_STRINGS_EXTRA_H_

#ifndef WIFI_MANAGER_MAX_OPTIONS
#define WIFI_MANAGER_MAX_OPTIONS 5  // params will autoincrement and realloc by this amount when max is reached
#endif

const char HTTP_FORM_PARAM[] PROGMEM = "<input id='{i}' name='{n}' maxlength='{l}' value='{v}'>";  // do not remove newline!
const char HTTP_FORM_PARAM_PASS[] PROGMEM = "<input type='password' id='{i}' name='{n}' maxlength='{l}'>";
const char HTTP_FORM_PARAM_CHECKBOX[] PROGMEM = "<input type='checkbox' id='{i}' name='{n}' value='true'{C}>";
const char HTTP_FORM_PARAM_SELECT[] PROGMEM = "<select id='{i}' name='{n}'>{o}</select>";
const char HTTP_FORM_PARAM_SELECT_OPTION[] PROGMEM = "<option value='{v}'{s}>{l}</option>\n";
const char HTTP_FORM_PARAM_RADIO[] PROGMEM = "<input type='radio' id='{i}' name='{n}' value='{ov}'{C}><label for='{on}'>{ol}</label>";
const char HTTP_FORM_PARAM_CHECKED[] PROGMEM = " checked";
const char HTTP_FORM_PARAM_SELECTED[] PROGMEM = " selected";
const char HTTP_FORM_PARAM_SPACER[] PROGMEM = "<hr>";
const char HTTP_FORM_PARAM_STRING[] PROGMEM = "<input id='{i}' name='{n}' maxlength='{l}' value='{v}'>";  // do not remove newline!
const char HTTP_FORM_PARAM_INT[] PROGMEM =
    "<input type='number' id='{i}' name='{n}' maxlength='{l}' value='{v}' min='{m}' max='{M}'>";  // do not remove newline!
const char HTTP_FORM_LABEL[] PROGMEM = "<label for='{i}'>{t}</label>";
const char HTTP_FORM_ENDLINE[] PROGMEM = "<br/>";

const char T_o[] PROGMEM = "{o}";    // @token o
const char T_s[] PROGMEM = "{s}";    // @token s
const char T_C[] PROGMEM = "{C}";    // @token C
const char T_ov[] PROGMEM = "{ov}";  // @token ov
const char T_on[] PROGMEM = "{on}";  // @token on
const char T_ol[] PROGMEM = "{ol}";  // @token on
const char T_t[] PROGMEM = "{t}";    // @token t
const char T_i[] PROGMEM = "{i}";    // @token i
const char T_n[] PROGMEM = "{n}";    // @token n
const char T_v[] PROGMEM = "{v}";    // @token v
const char T_l[] PROGMEM = "{l}";    // @token l
const char T_m[] PROGMEM = "{m}";    // @token m
const char T_M[] PROGMEM = "{M}";    // @token M

#endif