#include "WiFiManagerParameter.h"
String build_label_and_option(String option_template, LabelPlace place) {
    if (place == LabelPlace::LABEL_BEFORE) {
        String html;
        html = FPSTR(HTTP_FORM_LABEL);
        html += FPSTR(HTTP_FORM_ENDLINE);
        html += option_template;
        html += FPSTR(HTTP_FORM_ENDLINE);
        return html;
    }
    if (place == LabelPlace::LABEL_AFTER) {
        String html;
        html = option_template;
        html += FPSTR(HTTP_FORM_ENDLINE);
        html += FPSTR(HTTP_FORM_LABEL);
        html += FPSTR(HTTP_FORM_ENDLINE);
        return html;
    }
    return option_template + FPSTR(HTTP_FORM_ENDLINE);
}

String replaceLabel(String rawhtml, String label) {
    rawhtml.replace(FPSTR(T_t), label);
    return rawhtml;
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameter
 * --------------------------------------------------------------------------------
 **/

WiFiManagerParameter::WiFiManagerParameter() {
    _id = NULL;
    _label = NULL;
    setNewValue("");
    setMaxLength(10);
    setLabelPlace(LabelPlace::NO_LABEL);
}

void WiFiManagerParameter::init(const char *id, const char *label, int max_length, LabelPlace label_place) {
    _id = id;
    setLabel(label);
    setMaxLength(max_length);
    setLabelPlace(label_place);
}

char *WiFiManagerParameter::copyString(const char *source, char *target) {
    int len_of_new_value = strlen(source);
    if (len_of_new_value > getMaxLength()) {
        return target;
    }

    target = new char[len_of_new_value + 1];
    memset(target, 0, len_of_new_value + 1);  // explicit null

    if (source != NULL) {
        strncpy(target, source, len_of_new_value);
    }
    return target;
}

String WiFiManagerParameter::getHTML() {
    char valLength[5];

    String param_item_html = replaceLabel(build_label_and_option(getHTMLTemplate(), getLabelPlace()), getLabel());

    if (getID() != NULL) {
        param_item_html.replace(FPSTR(T_i), getID());  // T_i id name
        param_item_html.replace(FPSTR(T_n), getID());  // T_n id name alias
        snprintf(valLength, 5, "%d", getMaxLength());
        param_item_html.replace(FPSTR(T_l), valLength);         // T_l value length
        param_item_html.replace(FPSTR(T_v), getStringValue());  // T_v value
    }
    return param_item_html;
}

void WiFiManagerParameter::item_to_json(JsonDocument &doc) { doc[_id] = getStringValue(); }

void WiFiManagerParameter::item_from_json(JsonDocument &doc) {
    if (doc.containsKey(_id)) {
        setNewValue(doc[_id].as<const char *>());
    }
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterString
 * --------------------------------------------------------------------------------
 **/

WiFiManagerParameterString::WiFiManagerParameterString() : WiFiManagerParameter() { setValue(""); }

void WiFiManagerParameterString::init(const char *id, const char *label, int max_length, LabelPlace label_place, const char *default_value) {
    WiFiManagerParameter::init(id, label, max_length, label_place);
    setValue(default_value);
}

void WiFiManagerParameterString::setValue(const char *new_value) { _value = copyString(new_value, _value); };

void WiFiManagerParameterString::setNewValue(const char *new_val) { _value = copyString(new_val, _value); }

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterPassword
 * --------------------------------------------------------------------------------
 **/

void WiFiManagerParameterPassword::setNewValue(const char *new_val) {
    if (strlen(new_val) == 0) {
        return;
    }
    char *val;
    val = copyString(new_val, val);
    setValue(val);
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterInt
 * --------------------------------------------------------------------------------
 **/

void WiFiManagerParameterInt::init(const char *id, const char *label, int max_length, LabelPlace label_place, int default_value, int min_value,
                                   int max_value) {
    WiFiManagerParameter::init(id, label, max_length, label_place);
    setMinValue(min_value);
    setMaxValue(max_value);
    setValue(default_value);
}

const char *WiFiManagerParameterInt::getStringValue() {
    char *string_val = new char[getMaxLength() + 1];
    memset(string_val, 0, getMaxLength() + 1);
    itoa(_value, string_val, 10);
    return string_val;
};
void WiFiManagerParameterInt::setNewValue(const char *new_val) { _value = atoi(new_val); }

String WiFiManagerParameterInt::getHTML() {
    char valLength[5];

    String param_item_html = WiFiManagerParameter::getHTML();
    param_item_html.replace(FPSTR(T_m), String(getMinValue()));
    param_item_html.replace(FPSTR(T_M), String(getMaxValue()));

    return param_item_html;
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterBoolean
 * --------------------------------------------------------------------------------
 **/

void WiFiManagerParameterBoolean::init(const char *id, const char *label, LabelPlace label_place, bool default_value) {
    WiFiManagerParameter::init(id, label, 10, label_place);
    setValue(default_value);
}

const char *WiFiManagerParameterBoolean::getStringValue() {
    if (_value) {
        return "true";
    }
    return "false";
};

void WiFiManagerParameterBoolean::setNewValue(const char *new_val) {
    if (strcmp(new_val, "true") == 0) {
        _value = true;
        return;
    }
    _value = false;
}

String WiFiManagerParameterBoolean::getHTML() {
    String html = WiFiManagerParameter::getHTML();
    if (_value) {
        html.replace(FPSTR(T_C), FPSTR(HTTP_FORM_PARAM_CHECKED));  // T_T label
    } else {
        html.replace(FPSTR(T_C), "");  // T_T label
    }
    return html;
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterSelectOption
 * --------------------------------------------------------------------------------
 **/
WiFiManagerParameterSelectOption::WiFiManagerParameterSelectOption(int value, const char *label) {
    setValue(value);
    setLabel(label);
}

void WiFiManagerParameterSelectOption::setLabel(const char *new_label) { _label = new_label; }

const char *WiFiManagerParameterSelectOption::getStringValue() {
    char *string_val = new char[6];
    memset(string_val, 0, 6);
    itoa(_value, string_val, 10);
    return string_val;
}

String WiFiManagerParameterSelectOption::getHTML() {
    //     char valLength[5];

    String html;
    html = getHTMLTemplate();
    html.replace(FPSTR(T_l), getLabel());
    html.replace(FPSTR(T_v), getStringValue());
    return html;
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterSelect
 * --------------------------------------------------------------------------------
 **/

WiFiManagerParameterSelect::WiFiManagerParameterSelect() : WiFiManagerParameterInt() {
    _paramsCount = 0;
    _max_params = WFM_MAX_OPTIONS;
    setValue(0);
}

void WiFiManagerParameterSelect::init(const char *id, const char *label, LabelPlace label_place, int default_value, int min_value, int max_value) {
    WiFiManagerParameterInt::init(id, label, 10, label_place, default_value, min_value, max_value);
}

void WiFiManagerParameterSelect::addOption(WiFiManagerParameterSelectOption *p) {
    // init params if never malloc
    if (_params == NULL) {
        _params = (WiFiManagerParameterSelectOption **)malloc(_max_params * sizeof(WiFiManagerParameterSelectOption *));
    }

    // resize the params array by increment of WIFI_MANAGER_MAX_PARAMS
    if (_paramsCount == _max_params) {
        _max_params += WFM_MAX_OPTIONS;
        WiFiManagerParameterSelectOption **new_params =
            (WiFiManagerParameterSelectOption **)realloc(_params, _max_params * sizeof(WiFiManagerParameterSelectOption *));
        if (new_params == NULL) {
            return;
        }
        _params = new_params;
    }

    _params[_paramsCount] = p;
    _paramsCount++;
}

String WiFiManagerParameterSelect::getHTML() {
    //     char valLength[5];

    String optionshtml = "";
    for (int i = 0; i < _paramsCount; i++) {
        if (_params[i] == NULL) {
            break;
        }
        String this_option_html = _params[i]->getHTML();
        if (_params[i]->getValue() == getValue()) {
            this_option_html.replace(FPSTR(T_s), FPSTR(HTTP_FORM_PARAM_SELECTED));
        } else {
            this_option_html.replace(FPSTR(T_s), "");
        }
        optionshtml += this_option_html;
    }

    String param_item_html = replaceLabel(build_label_and_option(getHTMLTemplate(), getLabelPlace()), getLabel());
    param_item_html.replace(FPSTR(T_i), getID());
    param_item_html.replace(FPSTR(T_n), getID());
    param_item_html.replace(FPSTR(T_l), getLabel());
    param_item_html.replace(FPSTR(T_o), optionshtml);
    param_item_html.replace(FPSTR(T_v), getStringValue());

    return param_item_html;
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterSpacer
 * --------------------------------------------------------------------------------
 **/
WiFiManagerParameterSpacer::WiFiManagerParameterSpacer(const char *label) { setLabel(label); }
String WiFiManagerParameterSpacer::getHTML() { return getHTMLTemplate() + FPSTR(HTTP_FORM_ENDLINE); };

// void WiFiManagerParameterBoolean::item_to_json(JsonDocument &doc) { doc[getID()] = getValue(); }

// void WiFiManagerParameterBoolean::item_from_json(JsonDocument &doc) {
//     if (doc.containsKey(getID())) {
//         setValue(doc[getID()]);
//     }
// }
//----------------

// WiFiManagerParameterBase::~WiFiManagerParameterBase() {
//     if (_new_value != NULL) {
//         delete[] _new_value;
//     }
//     _current_length = 0;  // setting length 0, ideally the entire parameter should be removed, or added to wifimanager scope so it follows
// }

// void WiFiManagerParameterBase::setValue(const char *new_value, int length) {
//     if (!_id) {
//         // Serial.println("cannot set value of this parameter");
//         return;
//     }

//     if (strlen(new_value) > _max_length) {
//         // Serial.println("defaultValue length mismatch");
//         return;
//     }

//     _current_length = length;
//     _new_value = new char[_current_length + 1];
//     memset(_new_value, 0, _current_length + 1);  // explicit null

//     if (new_value != NULL) {
//         strncpy(_new_value, new_value, _current_length);
//     }
//     parseValue();
// }

// const char *WiFiManagerParameterBase::getValue() const {
//     // Serial.println(printf("Address of _value is %p\n", (void *)_value));
//     return _new_value;
// }
// const char *WiFiManagerParameterBase::getID() const { return _id; }
// // const char *WiFiManagerParameterBase::getPlaceholder() const { return _label; }
// const char *WiFiManagerParameterBase::getLabel() const { return _label; }
// int WiFiManagerParameterBase::getValueLength() const { return _current_length; }
// int WiFiManagerParameterBase::getMaxLength() const { return _max_length; }

// void WiFiManagerParameterBase::item_to_json(JsonDocument &doc) { doc[_id] = getValue(); }

// void WiFiManagerParameterBase::item_from_json(JsonDocument &doc) {
//     if (doc.containsKey(_id)) {
//         setValue(doc[_id], strlen(doc[_id]));
//     }
// }

// void WiFiManagerParameterBase::setValueFromString(String newValue) {
//     if (newValue.length() > _max_length) {
//         return;
//     }
//     _current_length = newValue.length();
//     _new_value = new char[_current_length + 1];
//     memset(_new_value, 0, _current_length + 1);  // explicit null

//     if (newValue.c_str() != NULL) {
//         strncpy(_new_value, newValue.c_str(), _current_length);
//     }
//     parseValue();
// }

// WiFiManagerParameter::WiFiManagerParameter() {}

// // WiFiManagerParameter::WiFiManagerParameter(const char *custom) : WiFiManagerParameterBase() {
// //     _labelPlacement = WFM_LABEL_BEFORE;
// //     _customHTML = custom;
// // }

// // WiFiManagerParameter::WiFiManagerParameter(const char *id, const char *label) : WiFiManagerParameterBase(id, label, "", 1) {
// //     _labelPlacement = WFM_LABEL_BEFORE;
// //     _customHTML = "";
// // }

// // void WiFiManagerParameter::init(const char *id, const char *label, const char *defaultValue, int length)
// //     : WiFiManagerParameterBase(id, label, defaultValue, length) {

// //     _labelPlacement = WFM_LABEL_BEFORE;
// //     _customHTML = "";
// // }

// void WiFiManagerParameter::init(const char *id, const char *label, const char *defaultValue, int length, int labelPlacement) {
//     WiFiManagerParameterBase::init(id, label, defaultValue, length);
//     _labelPlacement = labelPlacement;
// }

// // @note debug is not available in wmparameter class

// int WiFiManagerParameter::getLabelPlacement() const { return _labelPlacement; }
// const char *WiFiManagerParameter::getCustomHTML() const { return _customHTML; }

// String WiFiManagerParameter::getHTML() {
//     char valLength[5];

//     String pitem;
//     switch (getLabelPlacement()) {
//         case WFM_LABEL_BEFORE:
//             pitem = FPSTR(HTTP_FORM_LABEL);
//             pitem += getHTMLTemplate();
//             break;
//         case WFM_LABEL_AFTER:
//             pitem = getHTMLTemplate();
//             pitem += FPSTR(HTTP_FORM_LABEL);
//             break;
//         default:
//             // WFM_NO_LABEL
//             pitem = getHTMLTemplate();
//             break;
//     }

//     // Input templating
//     // "<br/><input id='{i}' name='{n}' maxlength='{l}' value='{v}' {c}>";
//     // if no ID use customhtml for item, else generate from param string
//     if (getID() != NULL) {
//         pitem.replace(FPSTR(T_t), getLabel());  // T_T label

//         pitem.replace(FPSTR(T_i), getID());  // T_i id name
//         pitem.replace(FPSTR(T_n), getID());  // T_n id name alias
//         snprintf(valLength, 5, "%d", getMaxLength());
//         pitem.replace(FPSTR(T_l), valLength);   // T_l value length
//         pitem.replace(FPSTR(T_v), getStringValue());  // T_v value
//         // pitem.replace(FPSTR(T_c), getCustomHTML());  // T_c meant for additional attributes, not html, but can stuff
//     } else {
//         pitem = getCustomHTML();
//     }
//     return pitem;
// }

// String WiFiManagerParameter::getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM); }

// // bool WiFiManagerParameter::addOption(WiFiManagerParameterSelectOption *p) {
// //     // check param id is valid, unless null
// //     if (p->getID()) {
// //         for (size_t i = 0; i < strlen(p->getID()); i++) {
// //             if (!(isAlphaNumeric(p->getID()[i])) && !(p->getID()[i] == '_')) {
// //                 return false;
// //             }
// //         }
// //     }

// //     // init params if never malloc
// //     if (_options == NULL) {
// //         _options = (WiFiManagerParameterOption **)malloc(_max_options * sizeof(WiFiManagerParameterOption *));
// //     }

// //     // resize the params array by increment of WIFI_MANAGER_MAX_OPTIONS
// //     if (_optionsCount == _max_options) {
// //         _max_options += WIFI_MANAGER_MAX_OPTIONS;
// //         WiFiManagerParameterOption **new_options =
// //             (WiFiManagerParameterOption **)realloc(_options, _max_options * sizeof(WiFiManagerParameterOption *));
// //         if (new_options != NULL) {
// //             _options = new_options;
// //         } else {
// //             return false;
// //         }
// //     }

// //     _options[_optionsCount] = p;
// //     _optionsCount++;

// // #ifdef WM_DEBUG_LEVEL
// //     // DEBUG_WM(DEBUG_VERBOSE, F("Added Parameter:"), p->getID());
// // #endif
// //     return true;
// // }

// WiFiManagerParameterString::WiFiManagerParameterString() : WiFiManagerParameter() {}

// WiFiManagerParameterString::WiFiManagerParameterString(const char *id, const char *label, const char *defaultValue, int length, int
// labelPlacement)
// {
//     WiFiManagerParameter::init(id, label, defaultValue, length, labelPlacement);
// }
// String WiFiManagerParameterString::getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_STRING); }

// void WiFiManagerParameterString::parseValue() {
//     _current_length = strlen(_new_value);
//     _value = new char[_current_length + 1];
//     memset(_value, 0, _current_length + 1);  // explicit null

//     if (_new_value != NULL) {
//         strncpy(_value, _new_value, _current_length);
//     }
//     Serial.println("YES");
// }

// void WiFiManagerParameterInt::init(const char *id, const char *label, int defaultValue, int length, int labelPlacement) {
//     _value = defaultValue;
//     WiFiManagerParameter::init(id, label, "", length, labelPlacement);
// }
// String WiFiManagerParameterInt::getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_INT); };
// void WiFiManagerParameterInt::parseValue() {
//     if (strlen(_new_value)== 0){
//         return;
//     }
//     _value = atoi(_new_value); };

// const char *WiFiManagerParameterString::getValue() { return _value; }
// WiFiManagerParameterPassword::WiFiManagerParameterPassword() : WiFiManagerParameter() {}

// WiFiManagerParameterPassword::WiFiManagerParameterPassword(const char *id, const char *label) : WiFiManagerParameter(id, label) {}
// WiFiManagerParameterPassword::WiFiManagerParameterPassword(const char *id, const char *label, const char *defaultValue, int length)
//     : WiFiManagerParameter(id, label, defaultValue, length) {}
// WiFiManagerParameterPassword::WiFiManagerParameterPassword(const char *id, const char *label, const char *defaultValue, int length,
//                                                            int labelPlacement)
//     : WiFiManagerParameter(id, label, defaultValue, length, "", labelPlacement) {}
// String WiFiManagerParameterPassword::getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_PASS); }

// WiFiManagerParameterSelect::WiFiManagerParameterSelect() : WiFiManagerParameter() {}

// WiFiManagerParameterSelect::WiFiManagerParameterSelect(const char *id, const char *label) : WiFiManagerParameter(id, label) {}
// WiFiManagerParameterSelect::WiFiManagerParameterSelect(const char *id, const char *label, const char *defaultValue, int length)
//     : WiFiManagerParameter(id, label, defaultValue, length) {}
// WiFiManagerParameterSelect::WiFiManagerParameterSelect(const char *id, const char *label, const char *defaultValue, int length, int
// labelPlacement)
//     : WiFiManagerParameter(id, label, defaultValue, length, "", labelPlacement) {}
// String WiFiManagerParameterSelect::getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_SELECT); }

// String WiFiManagerParameterSelect::getHTML() {
//     String pitem;
//     switch (getLabelPlacement()) {
//         case WFM_LABEL_BEFORE:
//             pitem = FPSTR(HTTP_FORM_LABEL);
//             pitem += getHTMLTemplate();
//             break;
//         case WFM_LABEL_AFTER:
//             pitem = getHTMLTemplate();
//             pitem += FPSTR(HTTP_FORM_LABEL);
//             break;
//         default:
//             // WFM_NO_LABEL
//             pitem = getHTMLTemplate();
//             break;
//     }

//     // Input templating
//     // "<br/><input id='{i}' name='{n}' maxlength='{l}' value='{v}' {c}>";
//     // if no ID use customhtml for item, else generate from param string
//     String optionhtml;

//     if (_optionsCount > 0) {
//         // add the extra parameters to the form
//         for (int i = 0; i < _optionsCount; i++) {
//             if (_options[i] == NULL || _options[i]->getValueLength() == 0) {
//                 break;
//             }
//             String optiontemp = FPSTR(HTTP_FORM_PARAM_SELECT_OPTION);
//             optiontemp.replace(FPSTR(T_l), _options[i]->getLabel());  // T_T label
//             optiontemp.replace(FPSTR(T_v), _options[i]->getValue());  // T_T label
//             if (strcmp(_options[i]->getValue(), getValue()) == 0) {
//                 optiontemp.replace(FPSTR(T_s), FPSTR(HTTP_FORM_PARAM_CHECKED));  // T_T label
//             }
//             optionhtml += optiontemp;
//         }
//     }

//     if (getID() != NULL) {
//         pitem.replace(FPSTR(T_t), getLabel());  // T_T label

//         pitem.replace(FPSTR(T_i), getID());     // T_i id name
//         pitem.replace(FPSTR(T_n), getID());     // T_n id name alias
//         pitem.replace(FPSTR(T_o), optionhtml);  // T_n id name alias
//     } else {
//         pitem = getCustomHTML();
//     }
//     return pitem;
// }

// WiFiManagerParameterCheckBox::WiFiManagerParameterCheckBox() : WiFiManagerParameter() {}
// WiFiManagerParameterCheckBox::WiFiManagerParameterCheckBox(const char *id, const char *label) : WiFiManagerParameter(id, label, "true", 4) {}
// WiFiManagerParameterCheckBox::WiFiManagerParameterCheckBox(const char *id, const char *label, bool checked)
//     : WiFiManagerParameter(id, label, "true", 4) {
//     _checked = checked;
//     if (checked) {
//         setValue("true", 4);
//     }
// }

// WiFiManagerParameterCheckBox::WiFiManagerParameterCheckBox(const char *id, const char *label, bool checked, int labelPlacement)
//     : WiFiManagerParameter(id, label, "true", 4, "", labelPlacement) {
//     _checked = checked;
// }
// String WiFiManagerParameterCheckBox::getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_CHECKBOX); }

// String WiFiManagerParameterCheckBox::getHTML() {
//     String pitem;
//     switch (getLabelPlacement()) {
//         case WFM_LABEL_BEFORE:
//             pitem = FPSTR(HTTP_FORM_LABEL);
//             pitem += getHTMLTemplate();
//             break;
//         case WFM_LABEL_AFTER:
//             pitem = getHTMLTemplate();
//             pitem += FPSTR(HTTP_FORM_LABEL);
//             break;
//         default:
//             // WFM_NO_LABEL
//             pitem = getHTMLTemplate();
//             break;
//     }

//     // Input templating
//     // "<br/><input id='{i}' name='{n}' maxlength='{l}' value='{v}' {c}>";
//     // if no ID use customhtml for item, else generate from param string
//     if (getID() != NULL) {
//         pitem.replace(FPSTR(T_t), getLabel());  // T_T label

//         pitem.replace(FPSTR(T_i), getID());  // T_i id name
//         pitem.replace(FPSTR(T_n), getID());  // T_n id name alias
//         // snprintf(valLength, 5, "%d", getValueLength());
//         if (_checked) {
//             pitem.replace(FPSTR(T_C), FPSTR(HTTP_FORM_PARAM_CHECKED));  // T_T label
//         } else {
//             pitem.replace(FPSTR(T_C), "");  // T_T label
//         }

//         pitem.replace(FPSTR(T_v), getValue());       // T_v value
//         pitem.replace(FPSTR(T_c), getCustomHTML());  // T_c meant for additional attributes, not html, but can stuff
//     } else {
//         pitem = getCustomHTML();
//     }
//     return pitem;
// }

// bool WiFiManagerParameterCheckBox::isChecked() {
//     if (strcmp(getValue(), "true") == 0) {
//         _checked = true;
//     } else {
//         _checked = false;
//     }
//     return _checked;
// }

// WiFiManagerParameterOption::WiFiManagerParameterOption() {}

// WiFiManagerParameterOption::WiFiManagerParameterOption(const char *id, const char *label, const char *defaultValue, int length)
//     : WiFiManagerParameterBase(id, label, defaultValue, length) {}

// void WiFiManagerParameterOption::init(const char *id, const char *label, const char *defaultValue, int length) {
//     _id = id;
//     _label = label;
//     setValue(defaultValue, length);
// }

// void WiFiManagerParameterOption::setValue(const char *defaultValue, int length) {
//     if (!_id) {
//         // Serial.println("cannot set value of this parameter");
//         return;
//     }

//     _length = length;
//     _value = new char[_length + 1];
//     memset(_value, 0, _length + 1);  // explicit null

//     if (defaultValue != NULL) {
//         strncpy(_value, defaultValue, _length);
//     }
// }

// WiFiManagerParameterRadio::WiFiManagerParameterRadio() : WiFiManagerParameter() {}

// WiFiManagerParameterRadio::WiFiManagerParameterRadio(const char *id, const char *label) : WiFiManagerParameter(id, label) {}
// WiFiManagerParameterRadio::WiFiManagerParameterRadio(const char *id, const char *label, const char *defaultValue, int length)
//     : WiFiManagerParameter(id, label, defaultValue, length) {}
// WiFiManagerParameterRadio::WiFiManagerParameterRadio(const char *id, const char *label, const char *defaultValue, int length, int
// labelPlacement)
//     : WiFiManagerParameter(id, label, defaultValue, length, "", labelPlacement) {}
// String WiFiManagerParameterRadio::getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_SELECT); }

// String WiFiManagerParameterRadio::getHTML() {
//     // Input templating
//     // "<br/><input id='{i}' name='{n}' maxlength='{l}' value='{v}' {c}>";
//     // if no ID use customhtml for item, else generate from param string
//     String optionhtml;

//     if (_optionsCount > 0) {
//         // add the extra parameters to the form
//         for (int i = 0; i < _optionsCount; i++) {
//             if (_options[i] == NULL || _options[i]->getValueLength() == 0) {
//                 break;
//             }
//             String optiontemp = FPSTR(HTTP_FORM_PARAM_RADIO);
//             //"<br/><input type='radio' id='{i}' name='{n}' value='{ov}'><label for='{on}'>'{ol}'</label>";

//             optiontemp.replace(FPSTR(T_i), getID());                   // T_T id
//             optiontemp.replace(FPSTR(T_n), getID());                   // T_T id
//             optiontemp.replace(FPSTR(T_ov), _options[i]->getValue());  // T_T label
//             optiontemp.replace(FPSTR(T_on), _options[i]->getID());     // T_T label
//             optiontemp.replace(FPSTR(T_ol), _options[i]->getLabel());  // T_T label

//             if (strcmp(_options[i]->getValue(), getValue()) == 0) {
//                 optiontemp.replace(FPSTR(T_C), FPSTR(HTTP_FORM_PARAM_CHECKED));  // T_T label
//             } else {
//                 optiontemp.replace(FPSTR(T_C), "");  // T_T label
//             }
//             optionhtml += optiontemp;
//         }
//     }

//     String pitem;

//     switch (getLabelPlacement()) {
//         case WFM_LABEL_BEFORE:
//             pitem = FPSTR(HTTP_FORM_LABEL);
//             pitem += optionhtml;
//             break;
//         case WFM_LABEL_AFTER:
//             pitem = optionhtml;
//             pitem += FPSTR(HTTP_FORM_LABEL);
//             break;
//         default:
//             // WFM_NO_LABEL
//             pitem = optionhtml;
//             break;
//     }

//     if (getID() != NULL) {
//         pitem.replace(FPSTR(T_t), getLabel());  // T_T label

//         pitem.replace(FPSTR(T_i), getID());     // T_i id name
//         pitem.replace(FPSTR(T_n), getID());     // T_n id name alias
//         pitem.replace(FPSTR(T_o), optionhtml);  // T_n id name alias
//     } else {
//         pitem = getCustomHTML();
//     }
//     return pitem;
// }

// WiFiManagerParameterSpacer::WiFiManagerParameterSpacer() : WiFiManagerParameter() {}

// WiFiManagerParameterSpacer::WiFiManagerParameterSpacer(const char *id, const char *label) : WiFiManagerParameter(id, label) {}

// String WiFiManagerParameterSpacer::getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_SPACER); }

// String WiFiManagerParameterSpacer::getHTML() {
//     String pitem;

//     pitem = getHTMLTemplate();
//     pitem += FPSTR(HTTP_FORM_LABEL);
//     pitem += FPSTR(HTTP_BR);

//     // Input templating
//     // "<br/><input id='{i}' name='{n}' maxlength='{l}' value='{v}' {c}>";
//     // if no ID use customhtml for item, else generate from param string
//     if (getID() != NULL) {
//         pitem.replace(FPSTR(T_t), getLabel());  // T_T label
//         pitem.replace(FPSTR(T_i), getID());     // T_i id name
//     }
//     return pitem;
// }
