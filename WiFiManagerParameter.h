#ifndef WiFiManagerParameter_h
#define WiFiManagerParameter_h
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#include "strings_en.h"
#include "strings_en_extra.h"
#define WFM_LABEL_BEFORE 1
#define WFM_LABEL_AFTER 2
#define WFM_NO_LABEL 0
#define WFM_LABEL_DEFAULT 1

class WiFiManagerParameterBase {
   public:
    WiFiManagerParameterBase();
    WiFiManagerParameterBase(const char *id, const char *label, const char *defaultValue, int length);
    ~WiFiManagerParameterBase();
    // void init(const char *id, const char *label, const char *defaultValue, int length);

    const char *getID() const;
    const char *getValue() const;

    const char *getLabel() const;
    const char *getPlaceholder() const;  // @deprecated, use getLabel
    int getValueLength() const;

    void setValue(const char *defaultValue, int length);
    char *_value;
    int _length;
    void item_to_json(JsonDocument &doc);

   private:
    const char *_id;
    const char *_label;
};

class WiFiManagerParameterOption : public WiFiManagerParameterBase {
   public:
    WiFiManagerParameterOption();
    WiFiManagerParameterOption(const char *id, const char *label, const char *defaultValue, int length);
    void init(const char *id, const char *label, const char *defaultValue, int length);
    void setValue(const char *defaultValue, int length);

   private:
    WiFiManagerParameterOption &operator=(const WiFiManagerParameterOption &);
    const char *_id;
    const char *_label;
    int _length;
    char *_value;
};

class WiFiManagerParameter : public WiFiManagerParameterBase {
   public:
    /**
        Create custom parameters that can be added to the WiFiManager setup web page
        @id is used for HTTP queries and must not contain spaces nor other special characters
    */
    WiFiManagerParameter();
    WiFiManagerParameter(const char *custom);
    WiFiManagerParameter(const char *id, const char *label);
    WiFiManagerParameter(const char *id, const char *label, const char *defaultValue, int length);
    WiFiManagerParameter(const char *id, const char *label, const char *defaultValue, int length, const char *custom);
    WiFiManagerParameter(const char *id, const char *label, const char *defaultValue, int length, const char *custom, int labelPlacement);

    virtual String getHTML();
    virtual String getHTMLTemplate();
    bool addOption(WiFiManagerParameterOption *p);

    // WiFiManagerParameter& operator=(const WiFiManagerParameter& rhs);

    int getLabelPlacement() const;
    virtual const char *getCustomHTML() const;

    int _optionsCount = 0;
    WiFiManagerParameterOption **_options = NULL;

   protected:
    void init(const char *id, const char *label, const char *defaultValue, int length, const char *custom, int labelPlacement);

   private:
    WiFiManagerParameter &operator=(const WiFiManagerParameter &);

    int _labelPlacement;

    int _max_options;

   protected:
    const char *_customHTML;
    friend class WiFiManager;
};

class WiFiManagerParameterCheckBox : public WiFiManagerParameter {
   public:
    WiFiManagerParameterCheckBox();
    WiFiManagerParameterCheckBox(const char *id, const char *label);
    WiFiManagerParameterCheckBox(const char *id, const char *label, bool checked);
    WiFiManagerParameterCheckBox(const char *id, const char *label, bool checked, int labelPlacement);
    String getHTMLTemplate();
    String getHTML();
    bool isChecked();

   private:
    bool _checked = false;
};

class WiFiManagerParameterPassword : public WiFiManagerParameter {
   public:
    WiFiManagerParameterPassword();
    WiFiManagerParameterPassword(const char *id, const char *label);
    WiFiManagerParameterPassword(const char *id, const char *label, const char *defaultValue, int length);
    WiFiManagerParameterPassword(const char *id, const char *label, const char *defaultValue, int length, int labelPlacement);
    String getHTMLTemplate();
};

class WiFiManagerParameterSelect : public WiFiManagerParameter {
   public:
    WiFiManagerParameterSelect();
    WiFiManagerParameterSelect(const char *id, const char *label);
    WiFiManagerParameterSelect(const char *id, const char *label, const char *defaultValue, int length);
    WiFiManagerParameterSelect(const char *id, const char *label, const char *defaultValue, int length, int labelPlacement);
    String getHTMLTemplate();
    String getHTML();
};

class WiFiManagerParameterRadio : public WiFiManagerParameter {
   public:
    WiFiManagerParameterRadio();
    WiFiManagerParameterRadio(const char *id, const char *label);
    WiFiManagerParameterRadio(const char *id, const char *label, const char *defaultValue, int length);
    WiFiManagerParameterRadio(const char *id, const char *label, const char *defaultValue, int length, int labelPlacement);
    String getHTMLTemplate();
    String getHTML();
};

class WiFiManagerParameterSpacer : public WiFiManagerParameter {
   public:
    WiFiManagerParameterSpacer();
    WiFiManagerParameterSpacer(const char *id, const char *label);
    String getHTMLTemplate();
    String getHTML();
};

#endif