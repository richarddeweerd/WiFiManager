#ifndef WiFiManagerParameter_h
#define WiFiManagerParameter_h
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>

// #include "strings_en.h"
#include "strings_en_extra.h"
#define WFM_LABEL_BEFORE 1
#define WFM_LABEL_AFTER 2
#define WFM_NO_LABEL 0
#define WFM_LABEL_DEFAULT 1

#define WFM_MAX_OPTIONS 5

enum LabelPlace { LABEL_BEFORE, LABEL_AFTER, NO_LABEL };
String build_label_and_option(String option_template, LabelPlace place);
String replaceLabel(String rawhtml, String label);

class WiFiManagerParameter {
   public:
    WiFiManagerParameter();
    ~WiFiManagerParameter(){};

    void init(const char *id, const char *label, int max_length, LabelPlace label_place);

    const char *getID() const { return _id; };

    const char *getLabel() const { return _label; };
    void setLabel(const char *new_label) { _label = new_label; };
    char *copyString(const char *source, char *target);

    void setMaxLength(int max_lenght) { _max_length = max_lenght; };
    int getMaxLength() { return _max_length; };

    void setLabelPlace(LabelPlace label_place) { _label_place = label_place; };
    LabelPlace getLabelPlace() { return _label_place; };

    void setNewValue(String new_value) { setNewValue(new_value.c_str()); };

    virtual String getHTML();

    void item_to_json(JsonDocument &doc);
    void item_from_json(JsonDocument &doc);

    virtual const char *getStringValue() { return ""; };
    virtual void setNewValue(const char *new_value){};

    virtual String getHTMLTemplate() { return String(""); };

   private:
    char *_new_value;

    const char *_id;
    const char *_label;
    LabelPlace _label_place;
    int _max_length;
};

class WiFiManagerParameterString : public WiFiManagerParameter {
   public:
    WiFiManagerParameterString();
    ~WiFiManagerParameterString(){};
    void init(const char *id, const char *label, int max_length, LabelPlace label_place, const char *default_value);
    void setValue(const char *new_value);
    const char *getValue() { return _value; };

    // Virtual Overrides
    const char *getStringValue() { return _value; };
    void setNewValue(const char *new_val);
    String getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_STRING); };

   private:
    char *_value;
};

class WiFiManagerParameterPassword : public WiFiManagerParameterString {
   public:
    String getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_PASS); };
    void setNewValue(const char *new_val);
};

class WiFiManagerParameterInt : public WiFiManagerParameter {
   public:
    WiFiManagerParameterInt() : WiFiManagerParameter() { setValue(0); };
    ~WiFiManagerParameterInt(){};
    void init(const char *id, const char *label, int max_length, LabelPlace label_place, int default_value, int min_value, int max_value);
    void setValue(int new_value) { _value = new_value; };
    int getValue() { return _value; };
    void setMinValue(int new_value) { _min_value = new_value; };
    int getMinValue() { return _min_value; };
    void setMaxValue(int new_value) { _max_value = new_value; };
    int getMaxValue() { return _max_value; };
    // Virtual Overrides
    const char *getStringValue();
    void setNewValue(const char *new_val);
    String getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_INT); };

   private:
    int _value;
    int _min_value;
    int _max_value;
};

class WiFiManagerParameterBoolean : public WiFiManagerParameter {
   public:
    WiFiManagerParameterBoolean() : WiFiManagerParameter() { setValue(false); };
    ~WiFiManagerParameterBoolean(){};
    void init(const char *id, const char *label, LabelPlace label_place, bool default_value);
    void setValue(bool new_value) { _value = new_value; };
    bool getValue() { return _value; };

    // Override
    String getHTML();

    // Virtual Overrides
    const char *getStringValue();
    void setNewValue(const char *new_val);
    String getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_CHECKBOX); };

   private:
    bool _value;
};

class WiFiManagerParameterSelectOption {
   public:
    WiFiManagerParameterSelectOption(int value, const char *label);

    void setValue(int new_value) { _value = new_value; };
    int getValue() { return _value; };

    void setLabel(const char *new_label);
    const char *getLabel() const { return _label; };

    const char *getStringValue();

    String getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_SELECT_OPTION); };
    String getHTML();

   private:
    int _value;
    const char *_label;
};
class WiFiManagerParameterSelect : public WiFiManagerParameterInt {
   public:
    WiFiManagerParameterSelect();
    void init(const char *id, const char *label, LabelPlace label_place, int default_value, int min_value, int max_value);

    void addOption(WiFiManagerParameterSelectOption *p);

    String getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_SELECT); };
    String getHTML();

    // WiFiManagerParameter
    int _paramsCount;
    int _max_params;
    WiFiManagerParameterSelectOption **_params = NULL;
};

class WiFiManagerParameterSpacer : public WiFiManagerParameter {
   public:
    WiFiManagerParameterSpacer(const char *label);
    String getHTMLTemplate() { return FPSTR(HTTP_FORM_PARAM_SPACER); };
    String getHTML();
};

// //    public:
// //     WiFiManagerParameterOption();
// //     WiFiManagerParameterOption(const char *id, const char *label, const char *defaultValue, int length);
// //     void init(const char *id, const char *label, const char *defaultValue, int length);
// //     void setValue(const char *defaultValue, int length);

// //    private:
// //     WiFiManagerParameterOption &operator=(const WiFiManagerParameterOption &);
// //     const char *_id;
// //     const char *_label;
// //     int _length;
// //     char *_value;
// // };

// class WiFiManagerParameterBase {
//    public:
//     WiFiManagerParameterBase();
//     void init(const char *id, const char *label, const char *defaultValue, int length);
//     ~WiFiManagerParameterBase();
//     // void init(const char *id, const char *label, const char *defaultValue,
//     // int length);

//     const char *getID() const;
//     const char *getValue() const;
//     const char *getLabel() const;
//     // const char *getPlaceholder() const;  // @deprecated, use getLabel
//     int getValueLength() const;
//     int getMaxLength() const;

//     void setValue(const char *defaultValue, int length);
//     const char *_new_value;
//     int _current_length;
//     int _max_length;
//     void item_to_json(JsonDocument &doc);
//     void item_from_json(JsonDocument &doc);
//     void setValueFromString(String newValue);
//     virtual void parseValue(){};
//     virtual const char *getStringValue(){};

//    private:
//     const char *_id;
//     const char *_label;
// };

// // class WiFiManagerParameterOption : public WiFiManagerParameterBase {
// //    public:
// //     WiFiManagerParameterOption();
// //     WiFiManagerParameterOption(const char *id, const char *label, const char *defaultValue, int length);
// //     void init(const char *id, const char *label, const char *defaultValue, int length);
// //     void setValue(const char *defaultValue, int length);

// //    private:
// //     WiFiManagerParameterOption &operator=(const WiFiManagerParameterOption &);
// //     const char *_id;
// //     const char *_label;
// //     int _length;
// //     char *_value;
// // };

// class WiFiManagerParameter : public WiFiManagerParameterBase {
//    public:
//     /**
//         Create custom parameters that can be added to the WiFiManager setup web
//        page
//         @id is used for HTTP queries and must not contain spaces nor other
//        special characters
//     */
//     WiFiManagerParameter();
//     // WiFiManagerParameter(const char *custom);
//     // WiFiManagerParameter(const char *id, const char *label);
//     // WiFiManagerParameter(const char *id, const char *label, const char *defaultValue, int length);
//     void init(const char *id, const char *label, const char *defaultValue, int length, int labelPlacement);

//     virtual String getHTML();
//     virtual String getHTMLTemplate();
//     // bool addOption(WiFiManagerParameterOption *p);

//     // WiFiManagerParameter& operator=(const WiFiManagerParameter& rhs);

//     int getLabelPlacement() const;
//     virtual const char *getCustomHTML() const;

//     int _optionsCount = 0;
//     // WiFiManagerParameterOption **_options = NULL;
//     void parseValue(){};
//     const char *getStringValue(){};

//    protected:
//     void init(const char *id, const char *label, const char *defaultValue, int length, const char *custom, int labelPlacement);

//    private:
//     WiFiManagerParameter &operator=(const WiFiManagerParameter &);

//     int _labelPlacement;

//     int _max_options;

//    protected:
//     const char *_customHTML;
//     friend class WiFiManager;
// };

// class WiFiManagerParameterString : public WiFiManagerParameter {
//    public:
//     WiFiManagerParameterString();
//     WiFiManagerParameterString(const char *id, const char *label, const char *defaultValue, int length, int labelPlacement);
//     String getHTMLTemplate();
//     void parseValue();
//     const char *getValue(){return _value};

//    private:
//     const char *_value;
// };

// class WiFiManagerParameterInt : public WiFiManagerParameter {
//    public:
//     WiFiManagerParameterInt(){};
//     void init(const char *id, const char *label, int defaultValue, int length, int labelPlacement);
//     String getHTMLTemplate();
//     void parseValue();
//     int getValue() { return _value; };

//    private:
//     int _value;
// };

// // class WiFiManagerParameterCheckBox : public WiFiManagerParameter {
// //    public:
// //     WiFiManagerParameterCheckBox();
// //     WiFiManagerParameterCheckBox(const char *id, const char *label);
// //     WiFiManagerParameterCheckBox(const char *id, const char *label, bool checked);
// //     WiFiManagerParameterCheckBox(const char *id, const char *label, bool checked, int labelPlacement);
// //     String getHTMLTemplate();
// //     String getHTML();
// //     bool isChecked();

// //    private:
// //     bool _checked = false;
// // };

// // class WiFiManagerParameterPassword : public WiFiManagerParameter {
// //    public:
// //     WiFiManagerParameterPassword();
// //     WiFiManagerParameterPassword(const char *id, const char *label);
// //     WiFiManagerParameterPassword(const char *id, const char *label, const char *defaultValue, int length);
// //     WiFiManagerParameterPassword(const char *id, const char *label, const char *defaultValue, int length, int labelPlacement);
// //     String getHTMLTemplate();
// // };

// // class WiFiManagerParameterSelect : public WiFiManagerParameter {
// //    public:
// //     WiFiManagerParameterSelect();
// //     WiFiManagerParameterSelect(const char *id, const char *label);
// //     WiFiManagerParameterSelect(const char *id, const char *label, const char *defaultValue, int length);
// //     WiFiManagerParameterSelect(const char *id, const char *label, const char *defaultValue, int length, int labelPlacement);
// //     String getHTMLTemplate();
// //     String getHTML();
// // };

// // class WiFiManagerParameterRadio : public WiFiManagerParameter {
// //    public:
// //     WiFiManagerParameterRadio();
// //     WiFiManagerParameterRadio(const char *id, const char *label);
// //     WiFiManagerParameterRadio(const char *id, const char *label, const char *defaultValue, int length);
// //     WiFiManagerParameterRadio(const char *id, const char *label, const char *defaultValue, int length, int labelPlacement);
// //     String getHTMLTemplate();
// //     String getHTML();
// // };

// // class WiFiManagerParameterSpacer : public WiFiManagerParameter {
// //    public:
// //     WiFiManagerParameterSpacer();
// //     WiFiManagerParameterSpacer(const char *id, const char *label);
// //     String getHTMLTemplate();
// //     String getHTML();
// // };

#endif