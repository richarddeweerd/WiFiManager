#include <gtest/gtest.h>

#include "WiFiManager.h"
#include "WiFiManagerParameter.h"
#include "arduinojson.h"

namespace {
/**
 * --------------------------------------------------------------------------------
 *  Helpers
 * --------------------------------------------------------------------------------
 **/
TEST(build_label_and_option, Base) {
    WiFiManagerParameter base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(build_label_and_option(String("test"), LabelPlace::LABEL_BEFORE).c_str(), "<label for='{i}'>{t}</label><br/>test<br/>");
    ASSERT_STREQ(build_label_and_option(String("test"), LabelPlace::LABEL_AFTER).c_str(), "test<br/><label for='{i}'>{t}</label><br/>");
    ASSERT_STREQ(build_label_and_option(String("test"), LabelPlace::NO_LABEL).c_str(), "test<br/>");
}

TEST(replaceLabel, Base) { ASSERT_STREQ(replaceLabel(String("l_{t}_l"), String("LAB")).c_str(), "l_LAB_l"); }

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameter
 * --------------------------------------------------------------------------------
 **/

TEST(WiFiManagerParameter, Base) {
    WiFiManagerParameter base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getID(), NULL);
    ASSERT_STREQ(base_param.getLabel(), NULL);
    ASSERT_EQ(base_param.getLabelPlace(), LabelPlace::NO_LABEL);
    ASSERT_EQ(base_param.getMaxLength(), 10);
    ASSERT_STREQ(base_param.getStringValue(), "");
}

TEST(WiFiManagerParameter, SetLabel) {
    WiFiManagerParameter base_param;
    base_param.setLabel("test");
    ASSERT_STREQ(base_param.getLabel(), "test");
    base_param.setLabel("test2");
    ASSERT_STREQ(base_param.getLabel(), "test2");
}

TEST(WiFiManagerParameter, LablePlace) {
    WiFiManagerParameter base_param;
    ASSERT_EQ(base_param.getLabelPlace(), LabelPlace::NO_LABEL);
    base_param.setLabelPlace(LabelPlace::LABEL_BEFORE);
    ASSERT_EQ(base_param.getLabelPlace(), LabelPlace::LABEL_BEFORE);
    base_param.setLabelPlace(LabelPlace::LABEL_AFTER);
    ASSERT_EQ(base_param.getLabelPlace(), LabelPlace::LABEL_AFTER);
}

TEST(WiFiManagerParameter, MaxLength) {
    WiFiManagerParameter base_param;
    ASSERT_EQ(base_param.getMaxLength(), 10);
    base_param.setMaxLength(20);
    ASSERT_EQ(base_param.getMaxLength(), 20);
}

TEST(WiFiManagerParameter, init) {
    WiFiManagerParameter base_param;
    base_param.init("base_id", "base_label", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getID(), "base_id");
    ASSERT_STREQ(base_param.getLabel(), "base_label");
    ASSERT_EQ(base_param.getLabelPlace(), LabelPlace::LABEL_BEFORE);
    ASSERT_EQ(base_param.getMaxLength(), 40);
    ASSERT_STREQ(base_param.getStringValue(), "");
}

TEST(WiFiManagerParameter, NewValue_c_str) {
    WiFiManagerParameter base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getStringValue(), "");
    base_param.setNewValue("test");
    ASSERT_STREQ(base_param.getStringValue(), "");
}

TEST(WiFiManagerParameter, NewValue_String) {
    WiFiManagerParameter base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getStringValue(), "");
    base_param.setNewValue(String("test"));
    ASSERT_STREQ(base_param.getStringValue(), "");
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterString
 * --------------------------------------------------------------------------------
 **/

TEST(WiFiManagerParameterString, Base) {
    WiFiManagerParameterString base_param;
    ASSERT_STREQ(base_param.getValue(), "");
    ASSERT_STREQ(base_param.getStringValue(), "");
}

TEST(WiFiManagerParameterString, init) {
    WiFiManagerParameterString base_param;
    base_param.init("base_id", "base_label", 40, LabelPlace::LABEL_BEFORE, "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getID(), "base_id");
    ASSERT_STREQ(base_param.getLabel(), "base_label");
    ASSERT_EQ(base_param.getLabelPlace(), LabelPlace::LABEL_BEFORE);
    ASSERT_EQ(base_param.getMaxLength(), 40);
    ASSERT_STREQ(base_param.getStringValue(), "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getValue(), "DEFAULT_MQTT_HOST");
}

TEST(WiFiManagerParameterString, setValue) {
    WiFiManagerParameterString base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getStringValue(), "");
    ASSERT_STREQ(base_param.getValue(), "");
    base_param.setValue("test");
    ASSERT_STREQ(base_param.getStringValue(), "test");
    ASSERT_STREQ(base_param.getValue(), "test");
}

TEST(WiFiManagerParameterString, setNewValue) {
    WiFiManagerParameterString base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getStringValue(), "");
    ASSERT_STREQ(base_param.getValue(), "");
    base_param.setNewValue("test");
    ASSERT_STREQ(base_param.getStringValue(), "test");
    ASSERT_STREQ(base_param.getValue(), "test");
}
TEST(WiFiManagerParameterString, getHTMLTemplate) {
    WiFiManagerParameterString base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getHTMLTemplate().c_str(), "<input id='{i}' name='{n}' maxlength='{l}' value='{v}'>");
}

TEST(WiFiManagerParameterString, getHTML_label_before) {
    WiFiManagerParameterString base_param;
    base_param.init("id", "Label", 40, LabelPlace::LABEL_BEFORE, "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getHTML().c_str(),
                 "<label for='id'>Label</label><br/><input id='id' name='id' maxlength='40' value='DEFAULT_MQTT_HOST'><br/>");
}

TEST(WiFiManagerParameterString, getHTML_label_after) {
    WiFiManagerParameterString base_param;
    base_param.init("id", "Label", 40, LabelPlace::LABEL_AFTER, "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getHTML().c_str(),
                 "<input id='id' name='id' maxlength='40' value='DEFAULT_MQTT_HOST'><br/><label for='id'>Label</label><br/>");
}

TEST(WiFiManagerParameterString, getHTML_no_label) {
    WiFiManagerParameterString base_param;
    base_param.init("id", "Label", 40, LabelPlace::NO_LABEL, "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getHTML().c_str(), "<input id='id' name='id' maxlength='40' value='DEFAULT_MQTT_HOST'><br/>");
}

TEST(WiFiManagerParameterString, from_JSON) {
    WiFiManagerParameterString base_param;
    base_param.init("id", "Label", 40, LabelPlace::NO_LABEL, "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getValue(), "DEFAULT_MQTT_HOST");
    DynamicJsonDocument doc(512);
    doc["id"] = "4321";
    base_param.item_from_json(doc);
    ASSERT_STREQ(base_param.getValue(), "4321");
}

TEST(WiFiManagerParameterString, to_JSON) {
    String json;
    DynamicJsonDocument doc(512);
    WiFiManagerParameterString base_param;
    base_param.init("id", "Label", 40, LabelPlace::NO_LABEL, "test value");
    base_param.item_to_json(doc);
    serializeJson(doc, json);
    ASSERT_STREQ(json.c_str(), "{\"id\":\"test value\"}");
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterPassword
 * --------------------------------------------------------------------------------
 **/

TEST(WiFiManagerParameterPassword, Base) {
    WiFiManagerParameterPassword base_param;
    ASSERT_STREQ(base_param.getValue(), "");
    ASSERT_STREQ(base_param.getStringValue(), "");
}

TEST(WiFiManagerParameterPassword, init) {
    WiFiManagerParameterPassword base_param;
    base_param.init("base_id", "base_label", 40, LabelPlace::LABEL_BEFORE, "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getID(), "base_id");
    ASSERT_STREQ(base_param.getLabel(), "base_label");
    ASSERT_EQ(base_param.getLabelPlace(), LabelPlace::LABEL_BEFORE);
    ASSERT_EQ(base_param.getMaxLength(), 40);
    ASSERT_STREQ(base_param.getStringValue(), "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getValue(), "DEFAULT_MQTT_HOST");
}

TEST(WiFiManagerParameterPassword, setValue) {
    WiFiManagerParameterPassword base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getStringValue(), "");
    ASSERT_STREQ(base_param.getValue(), "");
    base_param.setValue("test");
    ASSERT_STREQ(base_param.getStringValue(), "test");
    ASSERT_STREQ(base_param.getValue(), "test");
}

TEST(WiFiManagerParameterPassword, setNewValue) {
    WiFiManagerParameterPassword base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getStringValue(), "");
    ASSERT_STREQ(base_param.getValue(), "");
    base_param.setNewValue("test");
    ASSERT_STREQ(base_param.getStringValue(), "test");
    ASSERT_STREQ(base_param.getValue(), "test");
}

TEST(WiFiManagerParameterPassword, setNewValue_empty) {
    WiFiManagerParameterPassword base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getStringValue(), "");
    ASSERT_STREQ(base_param.getValue(), "");
    base_param.setNewValue("test");
    ASSERT_STREQ(base_param.getStringValue(), "test");
    ASSERT_STREQ(base_param.getValue(), "test");
    base_param.setNewValue("");
    ASSERT_STREQ(base_param.getStringValue(), "test");
    ASSERT_STREQ(base_param.getValue(), "test");
}

TEST(WiFiManagerParameterPassword, getHTMLTemplate) {
    WiFiManagerParameterPassword base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getHTMLTemplate().c_str(), "<input type='password' id='{i}' name='{n}' maxlength='{l}'>");
}

TEST(WiFiManagerParameterPassword, getHTML_label_before) {
    WiFiManagerParameterPassword base_param;
    base_param.init("id", "Label", 40, LabelPlace::LABEL_BEFORE, "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getHTML().c_str(), "<label for='id'>Label</label><br/><input type='password' id='id' name='id' maxlength='40'><br/>");
}

TEST(WiFiManagerParameterPassword, getHTML_label_after) {
    WiFiManagerParameterPassword base_param;
    base_param.init("id", "Label", 40, LabelPlace::LABEL_AFTER, "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getHTML().c_str(), "<input type='password' id='id' name='id' maxlength='40'><br/><label for='id'>Label</label><br/>");
}

TEST(WiFiManagerParameterPassword, getHTML_no_label) {
    WiFiManagerParameterPassword base_param;
    base_param.init("id", "Label", 40, LabelPlace::NO_LABEL, "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getHTML().c_str(), "<input type='password' id='id' name='id' maxlength='40'><br/>");
}

TEST(WiFiManagerParameterPassword, from_JSON) {
    WiFiManagerParameterPassword base_param;
    base_param.init("id", "Label", 40, LabelPlace::NO_LABEL, "DEFAULT_MQTT_HOST");
    ASSERT_STREQ(base_param.getValue(), "DEFAULT_MQTT_HOST");
    DynamicJsonDocument doc(512);
    doc["id"] = "4321";
    base_param.item_from_json(doc);
    ASSERT_STREQ(base_param.getValue(), "4321");
}

TEST(WiFiManagerParameterPassword, to_JSON) {
    String json;
    DynamicJsonDocument doc(512);
    WiFiManagerParameterPassword base_param;
    base_param.init("id", "Label", 40, LabelPlace::NO_LABEL, "test value");
    base_param.item_to_json(doc);
    serializeJson(doc, json);
    ASSERT_STREQ(json.c_str(), "{\"id\":\"test value\"}");
}
/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterInt
 * --------------------------------------------------------------------------------
 **/

TEST(WiFiManagerParameterInt, Base) {
    WiFiManagerParameterInt base_param;
    ASSERT_STREQ(base_param.getStringValue(), "0");
    ASSERT_EQ(base_param.getValue(), 0);
}

TEST(WiFiManagerParameterInt, init) {
    WiFiManagerParameterInt base_param;
    base_param.init("base_id", "base_label", 40, LabelPlace::LABEL_BEFORE, 1234, 0, 20000);
    ASSERT_STREQ(base_param.getID(), "base_id");
    ASSERT_STREQ(base_param.getLabel(), "base_label");
    ASSERT_EQ(base_param.getLabelPlace(), LabelPlace::LABEL_BEFORE);
    ASSERT_EQ(base_param.getMaxLength(), 40);
    ASSERT_STREQ(base_param.getStringValue(), "1234");
    ASSERT_EQ(base_param.getValue(), 1234);
}

TEST(WiFiManagerParameterInt, NewValue) {
    WiFiManagerParameterInt base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getStringValue(), "0");
    ASSERT_EQ(base_param.getValue(), 0);
    base_param.setValue(4321);
    ASSERT_STREQ(base_param.getStringValue(), "4321");
    ASSERT_EQ(base_param.getValue(), 4321);
}

TEST(WiFiManagerParameterInt, setNewValue) {
    WiFiManagerParameterInt base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getStringValue(), "0");
    ASSERT_EQ(base_param.getValue(), 0);
    base_param.setNewValue("4321");
    ASSERT_STREQ(base_param.getStringValue(), "4321");
    ASSERT_EQ(base_param.getValue(), 4321);
}

TEST(WiFiManagerParameterInt, getHTMLTemplate) {
    WiFiManagerParameterInt base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getHTMLTemplate().c_str(), "<input type='number' id='{i}' name='{n}' maxlength='{l}' value='{v}' min='{m}' max='{M}'>");
}

TEST(WiFiManagerParameterInt, getHTML_label_before) {
    WiFiManagerParameterInt base_param;
    base_param.init("id", "Label", 40, LabelPlace::LABEL_BEFORE, 1234, 1, 20000);
    ASSERT_STREQ(base_param.getHTML().c_str(),
                 "<label for='id'>Label</label><br/><input type='number' id='id' name='id' maxlength='40' value='1234' min='1' max='20000'><br/>");
}

TEST(WiFiManagerParameterInt, getHTML_label_after) {
    WiFiManagerParameterInt base_param;
    base_param.init("id", "Label", 40, LabelPlace::LABEL_AFTER, 1234, 1, 20000);
    ASSERT_STREQ(base_param.getHTML().c_str(),
                 "<input type='number' id='id' name='id' maxlength='40' value='1234' min='1' max='20000'><br/><label for='id'>Label</label><br/>");
}

TEST(WiFiManagerParameterInt, getHTML_no_label) {
    WiFiManagerParameterInt base_param;
    base_param.init("id", "Label", 40, LabelPlace::NO_LABEL, 1234, 1, 20000);
    ASSERT_STREQ(base_param.getHTML().c_str(), "<input type='number' id='id' name='id' maxlength='40' value='1234' min='1' max='20000'><br/>");
}

TEST(WiFiManagerParameterInt, from_JSON) {
    WiFiManagerParameterInt base_param;
    base_param.init("id", "Label", 40, LabelPlace::NO_LABEL, 1234, 0, 20000);
    ASSERT_EQ(base_param.getValue(), 1234);
    DynamicJsonDocument doc(512);
    doc["id"] = "4321";
    base_param.item_from_json(doc);
    ASSERT_EQ(base_param.getValue(), 4321);
}

TEST(WiFiManagerParameterInt, to_JSON) {
    String json;
    DynamicJsonDocument doc(512);
    WiFiManagerParameterInt base_param;
    base_param.init("id", "Label", 40, LabelPlace::NO_LABEL, 1234, 0, 20000);
    base_param.item_to_json(doc);
    serializeJson(doc, json);
    ASSERT_STREQ(json.c_str(), "{\"id\":\"1234\"}");
}
/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterBoolean
 * --------------------------------------------------------------------------------
 **/

TEST(WiFiManagerParameterBoolean, Base) {
    WiFiManagerParameterBoolean base_param;
    ASSERT_STREQ(base_param.getStringValue(), "false");
    ASSERT_EQ(base_param.getValue(), false);
}

TEST(WiFiManagerParameterBoolean, init) {
    WiFiManagerParameterBoolean base_param;
    base_param.init("base_id", "base_label", LabelPlace::LABEL_BEFORE, true);
    ASSERT_STREQ(base_param.getID(), "base_id");
    ASSERT_STREQ(base_param.getLabel(), "base_label");
    ASSERT_EQ(base_param.getLabelPlace(), LabelPlace::LABEL_BEFORE);
    ASSERT_EQ(base_param.getMaxLength(), 10);
    ASSERT_STREQ(base_param.getStringValue(), "true");
    ASSERT_EQ(base_param.getValue(), true);
}

TEST(WiFiManagerParameterBoolean, NewValue) {
    WiFiManagerParameterBoolean base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getStringValue(), "false");
    ASSERT_EQ(base_param.getValue(), false);
    base_param.setValue(true);
    ASSERT_STREQ(base_param.getStringValue(), "true");
    ASSERT_EQ(base_param.getValue(), true);
}

TEST(WiFiManagerParameterBoolean, setNewValue) {
    WiFiManagerParameterBoolean base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getStringValue(), "false");
    ASSERT_EQ(base_param.getValue(), false);
    base_param.setNewValue("true");
    ASSERT_STREQ(base_param.getStringValue(), "true");
    ASSERT_EQ(base_param.getValue(), true);
    base_param.setNewValue("false");
    ASSERT_STREQ(base_param.getStringValue(), "false");
    ASSERT_EQ(base_param.getValue(), false);
}

TEST(WiFiManagerParameterBoolean, getHTMLTemplate) {
    WiFiManagerParameterBoolean base_param;
    // base_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, LabelPlace::LABEL_BEFORE);
    ASSERT_STREQ(base_param.getHTMLTemplate().c_str(), "<input type='checkbox' id='{i}' name='{n}' value='true'{C}>");
}

TEST(WiFiManagerParameterBoolean, getHTML_label_before) {
    WiFiManagerParameterBoolean base_param;
    base_param.init("id", "Label", LabelPlace::LABEL_BEFORE, true);
    ASSERT_STREQ(base_param.getHTML().c_str(),
                 "<label for='id'>Label</label><br/><input type='checkbox' id='id' name='id' value='true' checked><br/>");
}

TEST(WiFiManagerParameterBoolean, getHTML_label_after) {
    WiFiManagerParameterBoolean base_param;
    base_param.init("id", "Label", LabelPlace::LABEL_AFTER, true);
    ASSERT_STREQ(base_param.getHTML().c_str(),
                 "<input type='checkbox' id='id' name='id' value='true' checked><br/><label for='id'>Label</label><br/>");
}

TEST(WiFiManagerParameterBoolean, getHTML_no_label) {
    WiFiManagerParameterBoolean base_param;
    base_param.init("id", "Label", LabelPlace::NO_LABEL, true);
    ASSERT_STREQ(base_param.getHTML().c_str(), "<input type='checkbox' id='id' name='id' value='true' checked><br/>");
}

TEST(WiFiManagerParameterBoolean, from_JSON) {
    WiFiManagerParameterBoolean base_param;
    base_param.init("id", "Label", LabelPlace::NO_LABEL, true);
    ASSERT_EQ(base_param.getValue(), true);
    DynamicJsonDocument doc(512);
    doc["id"] = "false";
    base_param.item_from_json(doc);
    ASSERT_EQ(base_param.getValue(), false);
}

TEST(WiFiManagerParameterBoolean, to_JSON) {
    String json;
    DynamicJsonDocument doc(512);
    WiFiManagerParameterBoolean base_param;
    base_param.init("id", "Label", LabelPlace::NO_LABEL, true);
    base_param.item_to_json(doc);
    serializeJson(doc, json);
    ASSERT_STREQ(json.c_str(), "{\"id\":\"true\"}");
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterSelectOption
 * --------------------------------------------------------------------------------
 **/

TEST(WiFiManagerParameterSelectOption, Base) {
    WiFiManagerParameterSelectOption base_option(1, "Label1");
    ASSERT_STREQ(base_option.getStringValue(), "1");
    ASSERT_EQ(base_option.getValue(), 1);
    ASSERT_STREQ(base_option.getLabel(), "Label1");
}

TEST(WiFiManagerParameterSelectOption, getHTMLTemplate) {
    WiFiManagerParameterSelectOption base_option(1, "Label1");
    ASSERT_STREQ(base_option.getHTMLTemplate().c_str(), "<option value='{v}'{s}>{l}</option>\n");
}

TEST(WiFiManagerParameterSelectOption, getHTML) {
    WiFiManagerParameterSelectOption base_option(1, "Label1");
    ASSERT_STREQ(base_option.getHTML().c_str(), "<option value='1'{s}>Label1</option>\n");
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterSelect
 * --------------------------------------------------------------------------------
 **/

TEST(WiFiManagerParameterSelect, Base) {
    WiFiManagerParameterSelect base_select;
    ASSERT_EQ(base_select._paramsCount, 0);
    ASSERT_STREQ(base_select.getStringValue(), "0");
    ASSERT_EQ(base_select.getValue(), 0);
    ASSERT_STREQ(base_select.getLabel(), NULL);
}

TEST(WiFiManagerParameterSelect, init) {
    WiFiManagerParameterSelect base_select;
    base_select.init("id", "Lab", LabelPlace::LABEL_BEFORE, 1, 0, 10);
    ASSERT_EQ(base_select._paramsCount, 0);
    ASSERT_STREQ(base_select.getID(), "id");
    ASSERT_EQ(base_select.getValue(), 1);
    ASSERT_STREQ(base_select.getLabel(), "Lab");
}

TEST(WiFiManagerParameterSelect, AddOption) {
    WiFiManagerParameterSelect base_select;
    base_select.init("id", "Lab", LabelPlace::LABEL_BEFORE, 1, 0, 10);
    WiFiManagerParameterSelectOption base_option1(1, "Label1");
    base_select.addOption(&base_option1);
    ASSERT_EQ(base_select._paramsCount, 1);
    ASSERT_STREQ(base_select._params[0]->getStringValue(), "1");
    ASSERT_STREQ(base_select._params[0]->getLabel(), "Label1");
}

TEST(WiFiManagerParameterSelect, AddOption_twice) {
    WiFiManagerParameterSelect base_select;
    base_select.init("id", "Lab", LabelPlace::LABEL_BEFORE, 1, 0, 10);
    WiFiManagerParameterSelectOption base_option1(2, "Label1");
    WiFiManagerParameterSelectOption base_option2(3, "Label2");
    base_select.addOption(&base_option1);
    base_select.addOption(&base_option2);

    ASSERT_EQ(base_select._paramsCount, 2);
    ASSERT_EQ(base_select._params[0]->getValue(), 2);
    ASSERT_STREQ(base_select._params[0]->getStringValue(), "2");
    ASSERT_STREQ(base_select._params[0]->getLabel(), "Label1");
    ASSERT_EQ(base_select._params[1]->getValue(), 3);
    ASSERT_STREQ(base_select._params[1]->getStringValue(), "3");
    ASSERT_STREQ(base_select._params[1]->getLabel(), "Label2");
}

TEST(WiFiManagerParameterSelect, getHTMLTemplate) {
    WiFiManagerParameterSelect base_select;
    base_select.init("id", "Lab", LabelPlace::LABEL_BEFORE, 1, 0, 20);
    ASSERT_STREQ(base_select.getHTMLTemplate().c_str(), "<select id='{i}' name='{n}'>{o}</select>");
}

TEST(WiFiManagerParameterSelect, getHTML) {
    WiFiManagerParameterSelect base_select;
    ASSERT_STREQ(base_select.getHTML().c_str(), "<select id='' name=''></select><br/>");
}

TEST(WiFiManagerParameterSelect, AddOption_get_html) {
    WiFiManagerParameterSelect base_select;
    base_select.init("id", "Lab", LabelPlace::LABEL_BEFORE, 1, 0, 10);

    WiFiManagerParameterSelectOption base_option1(1, "Label1");
    base_select.addOption(&base_option1);
    ASSERT_STREQ(base_select.getHTML().c_str(),
                 "<label for='id'>Lab</label><br/><select id='id' name='id'><option value='1' selected>Label1</option>\n</select><br/>");
}

TEST(WiFiManagerParameterSelect, AddOption_twice_get_html) {
    WiFiManagerParameterSelect base_select;
    base_select.init("id", "Lab", LabelPlace::LABEL_BEFORE, 1, 0, 10);

    WiFiManagerParameterSelectOption base_option1(1, "Label1");
    WiFiManagerParameterSelectOption base_option2(2, "Label2");
    base_select.addOption(&base_option1);
    base_select.addOption(&base_option2);

    // ASSERT_STREQ(base_option.getStringValue(), "1");
    ASSERT_EQ(base_select._paramsCount, 2);
    ASSERT_STREQ(base_select.getHTML().c_str(),
                 "<label for='id'>Lab</label><br/><select id='id' name='id'><option value='1' selected>Label1</option>\n<option "
                 "value='2'>Label2</option>\n</select><br/>");
}

/**
 * --------------------------------------------------------------------------------
 *  WiFiManagerParameterSpacer
 * --------------------------------------------------------------------------------
 **/

TEST(WiFiManagerParameterSpacer, getHTMLTemplate) {
    WiFiManagerParameterSpacer spacer("Label");
    ASSERT_STREQ(spacer.getHTMLTemplate().c_str(), "<hr>");
}

TEST(WiFiManagerParameterSpacer, getHTML) {
    WiFiManagerParameterSpacer spacer("Label");
    ASSERT_STREQ(spacer.getHTML().c_str(), "<hr><br/>");
}

// -------

// TEST(WiFiManagerParameterString, Base) {
//     WiFiManagerParameterString string_param;
//     string_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, 1);
//     ASSERT_STREQ(string_param._new_value, "DEFAULT_MQTT_HOST");
//     ASSERT_STREQ(string_param.getValue(), "DEFAULT_MQTT_HOST");
// }

// TEST(WiFiManagerParameterString, SetVal_Pos) {
//     WiFiManagerParameterString string_param;
//     string_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, 1);
//     ASSERT_STREQ(string_param._new_value, "DEFAULT_MQTT_HOST");
//     ASSERT_STREQ(string_param.getValue(), "DEFAULT_MQTT_HOST");
//     string_param.setValueFromString("TestValue");
//     ASSERT_STREQ(string_param._new_value, "TestValue");
//     ASSERT_STREQ(string_param.getValue(), "TestValue");
// }

// TEST(WiFiManagerParameterString, getHTMLTemplate) {
//     WiFiManagerParameterString string_param;
//     string_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, 1);
//     ASSERT_STREQ(string_param.getHTMLTemplate().c_str(), "<br/><input id='{i}' name='{n}' maxlength='{l}' value='{v}'>\n");
// }

// TEST(WiFiManagerParameterString, HTML) {
//     WiFiManagerParameterString string_param;
//     string_param.init("mqtt_server", "MQTT server", "DEFAULT_MQTT_HOST", 40, 1);
//     ASSERT_STREQ(string_param.getHTML().c_str(), "<label for='mqtt_server'>MQTT server</label><br/><input id='mqtt_server' name='mqtt_server'
//     maxlength='40' value='DEFAULT_MQTT_HOST'>\n");
// }

// TEST(WiFiManagerParameterInt, Base) {
//     WiFiManagerParameterInt int_param;
//     int_param.init("mqtt_port", "MQTT port", 1883, 6, 1);
//     ASSERT_EQ(int_param.getValue(), 1883);
// }

// TEST(WiFiManagerParameterInt, SetVal_Pos) {
//     WiFiManagerParameterInt int_param;
//     int_param.init("mqtt_port", "MQTT port", 1883, 6, 1);
//     ASSERT_EQ(int_param.getValue(), 1883);
//     int_param.setValueFromString("12345");
//     ASSERT_STREQ(int_param._new_value, "12345");
//     ASSERT_EQ(int_param.getValue(), 12345);
// }

// TEST(WiFiManagerParameterInt, getHTMLTemplate) {
//     WiFiManagerParameterInt int_param;
//     int_param.init("mqtt_port", "MQTT port", 1883, 6, 1);
//     ASSERT_STREQ(int_param.getHTMLTemplate().c_str(), "<br/><input typ='number' id='{i}' name='{n}' maxlength='{l}' value='{v}'>\n");
// }

// TEST(WiFiManagerParameterInt, HTML) {
//     WiFiManagerParameterInt int_param;
//     int_param.init("mqtt_port", "MQTT port", 1883, 6, 1);
//     ASSERT_STREQ(int_param.getHTML().c_str(), "<label for='mqtt_port'>MQTT port</label><br/><input id='mqtt_port' name='mqtt_port' maxlength='6'
//     value='1234'>\n");
// }

// TEST(ConfigItemBool, Base_No_Label) {
//     ConfigItemBool ci;
//     ci.init("tag", true);
//     ASSERT_EQ(ci.get(), true);
//     ci.set(false);
//     ASSERT_EQ(ci.get(), false);
// }

// TEST(ConfigItemBool, FromJSON) {
//     DynamicJsonDocument doc(512);

//     deserializeJson(doc, "{\"cfg\":{\"tag\":true}}");

//     JsonObject child_object = doc["cfg"];

//     ConfigItemBool ci;
//     ci.init("tag", "Label", false);

//     ASSERT_EQ(ci.get(), false);
//     ci.from_json(child_object);
//     ASSERT_EQ(ci.get(), true);
// }

// TEST(ConfigItemBool, ToJSON) {
//     String out;
//     ConfigItemBool ci;
//     ci.init("tag", "Label", true);
//     DynamicJsonDocument doc(512);
//     JsonObject child_object = doc.createNestedObject("cfg");
//     ci.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"tag\":true}}");
//     out = "";
//     ci.set(false);
//     ci.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"tag\":false}}");
// }

// TEST(ConfigItemInt, Base) {
//     ConfigItemInt ci;
//     ci.init("int", "label", 123);
//     ASSERT_EQ(ci.get(), 123);
//     ci.set(-10);
//     ASSERT_EQ(ci.get(), -10);
// }

// TEST(ConfigItemInt, Base_No_Label) {
//     ConfigItemInt ci;
//     ci.init("int", 123);
//     ASSERT_EQ(ci.get(), 123);
//     ci.set(-10);
//     ASSERT_EQ(ci.get(), -10);
// }

// TEST(ConfigItemInt, FromJSON) {
//     DynamicJsonDocument doc(512);

//     deserializeJson(doc, "{\"cfg\":{\"int\":56789}}");

//     JsonObject child_object = doc["cfg"];

//     ConfigItemInt ci;
//     ci.init("int", "label", 12345);

//     ASSERT_EQ(ci.get(), 12345);
//     ci.from_json(child_object);
//     ASSERT_EQ(ci.get(), 56789);
// }

// TEST(ConfigItemInt, FromJSON_negative) {
//     DynamicJsonDocument doc(512);
//     deserializeJson(doc, "{\"cfg\":{\"int\":-56789}}");

//     JsonObject child_object = doc["cfg"];

//     ConfigItemInt ci;
//     ci.init("int", "label", 12345);

//     ASSERT_EQ(ci.get(), 12345);
//     ci.from_json(child_object);
//     ASSERT_EQ(ci.get(), -56789);
// }

// TEST(ConfigItemInt, ToJSON) {
//     String out;
//     DynamicJsonDocument doc(512);
//     JsonObject child_object = doc.createNestedObject("cfg");

//     ConfigItemInt ci;
//     ci.init("int", "label", 12345);
//     ci.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"int\":12345}}");
//     out = "";
//     ci.set(-12347);
//     child_object = doc.createNestedObject("cfg");
//     ci.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"int\":-12347}}");
// }

// TEST(ConfigItemFloat, Base) {
//     ConfigItemFloat ci;
//     ci.init("float", "label", 123.02035);
//     EXPECT_FLOAT_EQ(ci.get(), 123.02035);
//     ci.set(-10.568);
//     EXPECT_FLOAT_EQ(ci.get(), -10.568);
// }

// TEST(ConfigItemFloat, Base_No_Label) {
//     ConfigItemFloat ci;
//     ci.init("float", 123.02035);
//     EXPECT_FLOAT_EQ(ci.get(), 123.02035);
//     ci.set(-10.568);
//     EXPECT_FLOAT_EQ(ci.get(), -10.568);
// }

// TEST(ConfigItemFloat, FromJSON) {
//     DynamicJsonDocument doc(512);

//     deserializeJson(doc, "{\"cfg\":{\"float\":56.789}}");

//     JsonObject child_object = doc["cfg"];

//     ConfigItemFloat ci;
//     ci.init("float", "label", 12345.456);

//     EXPECT_FLOAT_EQ(ci.get(), 12345.456);
//     ci.from_json(child_object);
//     EXPECT_FLOAT_EQ(ci.get(), 56.789001);
// }

// TEST(ConfigItemFloat, FromJSON_negative) {
//     DynamicJsonDocument doc(512);
//     deserializeJson(doc, "{\"cfg\":{\"float\":-56.789}}");

//     JsonObject child_object = doc["cfg"];

//     ConfigItemFloat ci;
//     ci.init("float", "label", 123.45);

//     EXPECT_FLOAT_EQ(ci.get(), 123.45);
//     ci.from_json(child_object);
//     EXPECT_FLOAT_EQ(ci.get(), -56.789);
// }

// TEST(ConfigItemFloat, ToJSON) {
//     String out;
//     DynamicJsonDocument doc(512);
//     JsonObject child_object = doc.createNestedObject("cfg");

//     ConfigItemFloat ci;
//     ci.init("float", "label", 12.3456789);
//     ci.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"float\":12.34567928}}");
//     out = "";
//     ci.set(-98.765432);
//     child_object = doc.createNestedObject("cfg");
//     ci.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"float\":-98.76543427}}");
// }

// TEST(ConfigItemString, Base) {
//     ConfigItemString ci;
//     ci.init("str", "label", "default Value");
//     ASSERT_STREQ(ci.get(), "default Value");
//     ci.set("string");
//     ASSERT_STREQ(ci.get(), "string");
// }
// TEST(ConfigItemString, Base_No_Label) {
//     ConfigItemString ci;
//     ci.init("str", "default Value");
//     ASSERT_STREQ(ci.get(), "default Value");
//     ci.set("string");
//     ASSERT_STREQ(ci.get(), "string");
// }
// TEST(ConfigItemString, FromJSON) {
//     DynamicJsonDocument doc(512);
//     deserializeJson(doc, "{\"cfg\":{\"str\":\"New String\"}}");
//     JsonObject child_object = doc["cfg"];

//     ConfigItemString ci;
//     ci.init("str", "label", "default Value");

//     ASSERT_STREQ(ci.get(), "default Value");
//     ci.from_json(child_object);
//     ASSERT_STREQ(ci.get(), "New String");
// }

// TEST(ConfigItemString, ToJSON) {
//     String out;
//     DynamicJsonDocument doc(512);
//     JsonObject child_object = doc.createNestedObject("cfg");

//     ConfigItemString ci;
//     ci.init("str", "label", "Test String");

//     ci.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"str\":\"Test String\"}}");

//     out = "";
//     child_object = doc.createNestedObject("cfg");

//     ci.set("New String");

//     ci.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"str\":\"New String\"}}");
// }

// TEST(ConfigItemIP, Base) {
//     ConfigItemIP ci;
//     ci.init("tag", "label", IPAddress(192, 168, 12, 34));
//     ASSERT_EQ(ci.get(), IPAddress(192, 168, 12, 34));
//     ci.set(IPAddress(192, 168, 34, 21));
//     ASSERT_EQ(ci.get(), IPAddress(192, 168, 34, 21));
// }
// TEST(ConfigItemIP, Base_No_Label) {
//     ConfigItemIP ci;
//     ci.init("tag", IPAddress(192, 168, 12, 34));
//     ASSERT_EQ(ci.get(), IPAddress(192, 168, 12, 34));
//     ci.set(IPAddress(192, 168, 34, 21));
//     ASSERT_EQ(ci.get(), IPAddress(192, 168, 34, 21));
// }
// TEST(ConfigItemIP, FromJSON) {
//     DynamicJsonDocument doc(512);
//     deserializeJson(doc, "{\"cfg\":{\"ip\":[127,0,15,46]}}");
//     JsonObject child_object = doc["cfg"];

//     ConfigItemIP ci;
//     ci.init("ip", "label", IPAddress(192, 168, 12, 34));

//     ASSERT_EQ(ci.get(), IPAddress(192, 168, 12, 34));
//     ci.from_json(child_object);
//     ASSERT_EQ(ci.get(), IPAddress(127, 0, 15, 46));
// }

// TEST(ConfigItemIP, ToJSON) {
//     String out;
//     DynamicJsonDocument doc(512);
//     JsonObject child_object = doc.createNestedObject("cfg");

//     ConfigItemIP ci;
//     ci.init("tag", "label", IPAddress(192, 168, 12, 34));

//     ci.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"tag\":[192,168,12,34]}}");

//     out = "";
//     child_object = doc.createNestedObject("cfg");

//     ci.set(IPAddress(18, 45, 62, 54));
//     ci.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"tag\":[18,45,62,54]}}");
// }

// TEST(ESPConfigManager, Create) {
//     ESPConfigManager ec;
//     EXPECT_EQ(ec._base_group, nullptr);
// }
// TEST(ConfigItem, Create) {
//     ConfigItem ci;
//     ci.setup("tag_item", "Label_Item");
//     EXPECT_STREQ(ci._id, "tag_item");
//     EXPECT_STREQ(ci._label, "Label_Item");
//     EXPECT_EQ(ci._sibling, nullptr);
// }

// TEST(ConfigGroup, Create) {
//     ConfigGroup cg;
//     cg.setup("tag_grp", "Label_Group");
//     EXPECT_STREQ(cg._id, "tag_grp");
//     EXPECT_STREQ(cg._label, "Label_Group");
//     EXPECT_EQ(cg._sibling, nullptr);
//     EXPECT_EQ(cg._child, nullptr);
// }

// TEST(ESPConfigManager, add_group) {
//     ESPConfigManager ec;
//     EXPECT_EQ(ec._base_group, nullptr);
//     ConfigGroup cg;
//     cg.setup("tag_grp", "Label_Group");
//     ec.add_group(&cg);
//     EXPECT_EQ(ec._base_group, &cg);
// }

// TEST(ESPConfigManager, add_2_groups) {
//     ESPConfigManager ec;
//     EXPECT_EQ(ec._base_group, nullptr);
//     ConfigGroup cg;
//     cg.setup("tag_grp", "Label_Group");
//     ConfigGroup cg2;
//     cg2.setup("tag_grp2", "Label_Group2");
//     ec.add_group(&cg);
//     ec.add_group(&cg2);
//     EXPECT_EQ(ec._base_group, &cg);
//     EXPECT_EQ(cg._sibling, &cg2);
// }

// TEST(ConfigGroup, add_item) {
//     ConfigGroup cg;
//     cg.setup("tag_grp", "Label_Group");
//     ConfigItemBool cb;
//     cb.init("tag", "label", true);
//     cg.add_child(&cb);
//     EXPECT_EQ(cg._child, &cb);
//     EXPECT_EQ(cb._sibling, nullptr);
// }

// TEST(ConfigGroup, add_2_items) {
//     ConfigGroup cg;
//     cg.setup("tag_grp", "Label_Group");
//     ConfigItemBool cb;
//     cb.init("tag", "label", true);
//     ConfigItemBool cb2;
//     cb2.init("tag", "label", true);
//     cg.add_child(&cb);
//     cg.add_child(&cb2);
//     EXPECT_EQ(cg._child, &cb);
//     EXPECT_EQ(cb._sibling, &cb2);
// }

// TEST(ConfigGroup, to_json) {
//     String out;
//     DynamicJsonDocument doc(512);
//     JsonObject child_object = doc.createNestedObject("cfg");

//     ConfigGroup cg;
//     cg.setup("tag_grp", "Label_Group");
//     cg.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{}}");
// }

// TEST(ConfigGroup, to_json_with_child) {
//     String out;
//     DynamicJsonDocument doc(512);
//     JsonObject child_object = doc.createNestedObject("cfg");

//     ConfigGroup cg;
//     cg.setup("tag_grp", "Label_Group");

//     cg.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{}}");

//     out = "";
//     ConfigItemBool ci;
//     ci.init("tag", "Label", true);

//     cg.add_child(&ci);
//     cg.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"tag_grp\":{\"tag\":true}}}");
// }

// TEST(ConfigGroup, from_json_with_child) {
//     DynamicJsonDocument doc(512);
//     deserializeJson(doc, "{\"cfg\":{\"tag_grp\":{\"tag\":true}}}");
//     JsonObject child_object = doc["cfg"];

//     ConfigGroup cg;
//     cg.setup("tag_grp", "Label_Group");

//     ConfigItemBool ci;
//     ci.init("tag", "Label", false);

//     cg.add_child(&ci);

//     ASSERT_EQ(ci.get(), false);
//     cg.from_json(child_object);
//     ASSERT_EQ(ci.get(), true);
// }

// TEST(ConfigGroup, to_json_with_2_children) {
//     String out;
//     DynamicJsonDocument doc(512);
//     JsonObject child_object = doc.createNestedObject("cfg");

//     ConfigGroup cg;
//     cg.setup("tag_grp", "Label_Group");

//     cg.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{}}");

//     out = "";
//     ConfigItemBool ci;
//     ci.init("bool", "Label", true);
//     ConfigItemInt cint;
//     cint.init("int", "Label", 12345);

//     cg.add_child(&ci);
//     cg.add_child(&cint);
//     cg.to_json(child_object);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"tag_grp\":{\"bool\":true,\"int\":12345}}}");
// }

// TEST(ConfigGroup, from_json_with_2_children) {
//     DynamicJsonDocument doc(512);
//     deserializeJson(doc, "{\"cfg\":{\"tag_grp\":{\"bool\":false, \"int\":12345}}}");
//     JsonObject child_object = doc["cfg"];

//     ConfigGroup cg;
//     cg.setup("tag_grp", "Label_Group");

//     ConfigItemBool ci;
//     ci.init("bool", "Label", true);
//     ConfigItemInt cint;
//     cint.init("int", "Label", -98765);

//     cg.add_child(&ci);
//     cg.add_child(&cint);
//     ASSERT_EQ(ci.get(), true);
//     ASSERT_EQ(cint.get(), -98765);
//     cg.from_json(child_object);
//     ASSERT_EQ(ci.get(), false);
//     ASSERT_EQ(cint.get(), 12345);
// }

// TEST(ESPConfigManager, set_wifissid) {
//     ESPConfigManager ec;
//     ec.set_wifissid("wifissid");
//     ASSERT_STREQ(ec.get_ssid(), "wifissid");
// }

// TEST(ESPConfigManager, set_wifikey) {
//     ESPConfigManager ec;
//     ec.set_wifikey("wifikey");
//     ASSERT_STREQ(ec.get_key(), "wifikey");
// }

// TEST(ESPConfigManager, set_wifi) {
//     ESPConfigManager ec;
//     ec.set_wifi("wifissid", "wifikey");
//     ASSERT_STREQ(ec.get_ssid(), "wifissid");
//     ASSERT_STREQ(ec.get_key(), "wifikey");
// }

// TEST(ESPConfigManager, save_to_json) {
//     String out;
//     DynamicJsonDocument doc(512);
//     ESPConfigManager ec;
//     ec.set_wifi("wifissid", "wifikey");
//     ec.save_to_json(doc);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"wifi\":{\"ssid\":\"wifissid\",\"key\":\"wifikey\"}}");
// }

// TEST(ESPConfigManager, save_wifi_to_json) {
//     String out;
//     DynamicJsonDocument doc(512);
//     ESPConfigManager ec;
//     ec.set_wifi("wifissid", "wifikey");
//     ec.save_wifi_json(doc);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"wifi\":{\"ssid\":\"wifissid\",\"key\":\"wifikey\"}}");
// }

// TEST(ESPConfigManager, save_to_json_empty_wifi) {
//     String out;
//     DynamicJsonDocument doc(512);
//     ESPConfigManager ec;
//     ec.save_wifi_json(doc);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "null");
// }

// TEST(ESPConfigManager, save_to_json_with_empty_base_group) {
//     String out;
//     DynamicJsonDocument doc(512);
//     ESPConfigManager ec;
//     ConfigGroup cg;
//     cg.setup("nw", "Network");
//     ec.set_wifi("wifissid", "wifikey");
//     ec.save_to_json(doc);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"wifi\":{\"ssid\":\"wifissid\",\"key\":\"wifikey\"}}");
// }

// TEST(ESPConfigManager, save_to_json_with_base_group_with_2_items) {
//     String out;
//     DynamicJsonDocument doc(512);
//     ESPConfigManager ec;
//     ec.set_wifi("wifissid", "wifikey");

//     ConfigGroup cg;
//     cg.setup("nw", "Network");

//     ConfigItemInt cint;
//     cint.init("int", "Label", 12345);

//     ConfigItemString cstr;
//     cstr.init("str", "Label", "text");
//     ec.add_group(&cg);
//     cg.add_child(&cint);
//     cg.add_child(&cstr);
//     ec.save_to_json(doc);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"wifi\":{\"ssid\":\"wifissid\",\"key\":\"wifikey\"},\"cfg\":{\"nw\":{\"int\":12345,\"str\":\"text\"}}}");
// }

// TEST(ESPConfigManager, save_to_json_with_2_base_groups) {
//     String out;
//     DynamicJsonDocument doc(1024);
//     ESPConfigManager ec;
//     ec.set_wifi("wifissid", "wifikey");

//     ConfigGroup cg;
//     cg.setup("nw");

//     ConfigGroup cg_data;
//     cg_data.setup("data");

//     ConfigItemInt cint;
//     cint.init("int", "Label", 12345);

//     ConfigItemString cstr;
//     cstr.init("str", "Label", "text");

//     cg.add_child(&cint);
//     cg_data.add_child(&cstr);
//     ec.add_group(&cg);
//     ec.add_group(&cg_data);
//     ec.save_to_json(doc);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(),
//     "{\"wifi\":{\"ssid\":\"wifissid\",\"key\":\"wifikey\"},\"cfg\":{\"nw\":{\"int\":12345},\"data\":{\"str\":\"text\"}}}");
// }

// TEST(ESPConfigManager, save_to_json_with_2_base_groups_no_wifi) {
//     String out;
//     DynamicJsonDocument doc(1024);
//     ESPConfigManager ec;
//     // ec.set_wifi("wifissid", "wifikey");

//     ConfigGroup cg;
//     cg.setup("nw");

//     ConfigGroup cg_data;
//     cg_data.setup("data");

//     ConfigItemInt cint;
//     cint.init("int", "Label", 12345);

//     ConfigItemString cstr;
//     cstr.init("str", "Label", "text");

//     cg.add_child(&cint);
//     cg_data.add_child(&cstr);
//     ec.add_group(&cg);
//     ec.add_group(&cg_data);
//     ec.save_to_json(doc);
//     serializeJson(doc, out);
//     ASSERT_STREQ(out.c_str(), "{\"cfg\":{\"nw\":{\"int\":12345},\"data\":{\"str\":\"text\"}}}");
// }

// TEST(ESPConfigManager, save_and_load_config) {
//     if (!LittleFS.begin()) {
//         // LittleFS.format();
//         Serial.println("An Error has occurred while mounting LittleFS");
//         return;
//     }

//     LittleFS.remove("/esp_cfg.json");
//     ESPConfigManager *esp_config = new ESPConfigManager();
//     ConfigGroup *config_group_nw = new ConfigGroup();
//     ConfigGroup *config_group_data = new ConfigGroup();
//     ConfigItemIP *cip = new ConfigItemIP();
//     ConfigItemInt *cint = new ConfigItemInt();
//     ConfigItemString *cstr = new ConfigItemString();

//     esp_config->set_wifi("wifissid", "wifikey");

//     config_group_nw->setup("nw");
//     config_group_data->setup("data");

//     cip->init("ipaddress", IPAddress(192, 168, 10, 196));
//     cint->init("int", 12345);   // Default value 12345
//     cstr->init("str", "text");  // Default value "text"

//     esp_config->add_group(config_group_nw);
//     esp_config->add_group(config_group_data);

//     config_group_nw->add_child(cint);
//     config_group_nw->add_child(cstr);

//     cint->set(108);         // Overwrite default value
//     cstr->set("New Text");  // Overwrite default value
//     esp_config->save();     // save

//     // delete esp_config;
//     // delete config_group_nw;
//     // delete cint;
//     // delete cstr;

//     esp_config = new ESPConfigManager();
//     config_group_nw = new ConfigGroup();
//     config_group_data = new ConfigGroup();
//     cint = new ConfigItemInt();
//     cstr = new ConfigItemString();

//     config_group_nw->setup("nw");
//     cint->init("int", 12345);   // Default value 12345
//     cstr->init("str", "text");  // Default value "text"

//     esp_config->add_group(config_group_nw);
//     config_group_nw->add_child(cint);
//     config_group_nw->add_child(cstr);

//     // ASSERT_STREQ(esp_config->get_ssid(), NULL);  // default value
//     // ASSERT_STREQ(esp_config->get_key(), NULL);   // default value

//     ASSERT_EQ(cint->get(), 12345);      // default value
//     ASSERT_STREQ(cstr->get(), "text");  // default value
//     esp_config->load();
//     ASSERT_EQ(cint->get(), 108);            // new value
//     ASSERT_STREQ(cstr->get(), "New Text");  // new value
// }

}  // namespace

#if defined(ARDUINO)
#include <Arduino.h>

void setup() {
    // should be the same value as for the `test_speed` option in "platformio.ini"
    // default value is test_speed=115200
    Serial.begin(115200);

    ::testing::InitGoogleTest();
    // if you plan to use GMock, replace the line above with
    // ::testing::InitGoogleMock();
}

void loop() {
    // Run tests
    if (RUN_ALL_TESTS())
        ;

    // sleep for 1 sec
    delay(60000);
}

#else
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // if you plan to use GMock, replace the line above with
    // ::testing::InitGoogleMock(&argc, argv);

    if (RUN_ALL_TESTS())
        ;

    // Always return zero-code and allow PlatformIO to parse results
    return 0;
}
#endif