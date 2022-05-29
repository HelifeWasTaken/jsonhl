/**
 * File              : JsonhlParser.hpp
 * Author            : Mattis DALLEAU <mattisdalleau@gmail.com>
 * Date              : 10.06.2021
 * Last Modified Date: 10.06.2021
 * Last Modified By  : Mattis DALLEAU <mattisdalleau@gmail.com>
 */
#pragma once

#include "JsonhlValue.hpp"
#include <fstream>

namespace jsonhl
{

class Parser
{

  private:
    std::string _buffer;
    std::size_t _index = 0;

    /* Parser/Parser.cpp */

    inline static const std::string SPACES_TOKENS = " \t\n";
    inline static const std::string TRUE_TOKEN = "true";
    inline static const std::string FALSE_TOKEN = "false";
    inline static const std::string NULL_TOKEN = "null";
    inline static const std::string NUMBER_TOKENS = "0123456789+-";

    /* Parser/ParseUtil.cpp */
  public:
    /**
     * @brief Check if the current character is one of the tokens
     *
     * @param c The char to search
     * @param tokens The token list
     * @return true Found c in tokens
     * @return false Did not found c in token
     */
    bool isToken(char const &c, const std::string &tokens) const;
    /**
     * @brief Skips '\t' '\n' ' ' by moving _index
     */
    void skipSpaces();

    /* Parser/ParseBoolean.cpp */
  public:
    /**
     * @brief Parse a Boolean value from a json
     *
     * @param conf The current node of Json
     * @return true Was a valid Json boolean value
     * @return false Wasn't recognized safely as a boolean value
     */
    bool parseBoolean(jsonhl::Value &conf);

    /* Parser/ParseNull.cpp */
  public:
    /**
     * @brief Parse a null value from a json
     *
     * @param conf The current node of Json
     * @return true Was a valid null value
     * @return false Wasn't recognized safely as a null value
     */
    bool parseNull(jsonhl::Value &conf);

    /* Parser/ParseNumber.cpp */
  private:
    /**
     * @brief Compute the value of the current number (throws if the current value is not a number)
     *
     * @param value The value to compute in
     */
    void ____MJsonStrtod(double &value);
    /**
     * @brief Compute the value of the current exponent (throws if the current value is invalid (not a number))
     *
     * @param originalValue The value to compute in
     */
    void ____MJsonParseExponent(double &originalValue);
    /**
     * @brief Compute the value of the current float calls ____MJsonParseExponent (if necessary)
     *        and _____MJsonStrtod(throws if the current value is invalid (not a number))
     *
     * @param originalValue The value to compute in
     */
    void ____MJsonParseFloatCompletely(double &FinalValue);
    /* Parser/ParseNumber.cpp */
  public:
    /**
     * @brief Parse a number from a json (If the value was well formed at start but gets a grammar problem in the middle
     * throws) Example:
     *              - "lol53" does not throws but return false
     *              - "53" does not throws and returns true
     *              - "53lol" throws
     *
     * @param conf The current node of Json
     * @return true Was a valid Json number
     * @return false Wasn't recognized safely as JsonNumber
     */
    bool parseNumber(jsonhl::Value &conf);

    /* Parser/ParseString.cpp */
  private:
    /**
     * @brief Expects that the first '"" has been skipped and tries to read a valid string
     *        If the string is not valid it throws, It also use the _index and _buffer
     *
     * @param buffer The buffer to write in
     */
    void ____MJsonReadString(std::string &buffer);

    /* Parser/ParseString.cpp */
  public:
    /**
     * @brief Parse a string from a json (if the string was well formed at start but gets a grammar problem in the
     * middle throws)
     *
     * @param conf The current node of Json
     * @return true Was a valid Json String
     * @return false Wasn't recognized safely as JsonString
     */
    bool parseString(jsonhl::Value &conf);

    /* Parser/ParseArray.cpp */
  private:
    /**
     * @brief Loops to read a Json Array (if the array has a grammar problem throws)
     *
     * @param conf The current Json Node
     * @param arr The array to append the values in
     */
    void ____MJsonReadArray(jsonhl::Value &conf, jsonhl::Value::Array &arr);
    /* Parser/ParseArray.cpp */
  public:
    /**
     * @brief Parse an array from a json (if the value was well formed at start but gets a grammar problem in the middle
     * throws) A jsonhl::Value::Array is in fact a jsonhl::Value::std::vector<jsonhl::Value>
     *
     * @param conf The current node of Json
     * @return true Was a valid JsonArray
     * @return false Wasn't recognized safely as a JsonArray
     */
    bool parseArray(jsonhl::Value &conf);

    /* Parser/ParseObject.cpp */
  private:
    /**
     * @brief This is used to gather one data from a Object it parses a jsonhl::Value::ValueType::STRING and a
     * jsonhl::Value (any ?) This might throw if the string parsed or the value is badly written
     * @param object The object to write in
     */
    void ____MJsonObjectReadData(jsonhl::Value::Object &object);
    /**
     * @brief Loop to call this->____MJsonObjectReadData until all the objects are read
     *        (It mights throws if the object is not well written) Notable
     *        with ____MJsonObjectReadData or because the object is not terminated
     *
     * @param conf The current Json Node
     * @param objects The Object to set the Key values
     */
    void ____MJsonParseObjectLoop(jsonhl::Value &conf, jsonhl::Value::Object &objects);
    /* Parser/ParseObject.cpp */
  public:
    /**
     * @brief Parse an object from a json (if the value was well formed at start but gets a grammar problem in the
     * middle throws) A jsonhl::Value::Object is in fact a jsonhl::Value::std::map<std::string, jsonhl::Value>
     *
     * @param conf The current node of Json
     * @return true Was a valid JsonObject
     * @return false Wasn't recognized safely as a JsonObject
     */
    bool parseObject(jsonhl::Value &conf);

    /* Parser/ParseValue.cpp */
  public:
    /**
     * @brief Call the good value parser to chose (might throw in one of them)
     *
     * @param conf The current JsonNode
     */
    void parseValue(jsonhl::Value &conf);

    /* Parser/Parser.cpp */
  public:
    /**
     * @brief Construct a new Parser object
     */
    Parser();
    /* Parser/Parser.cpp */
  public:
    /**
     * @brief Calls jsonhl::Parser and read jsonhl::Value
     *
     * @param filename The pathfile of the Json
     * @return Returns the first node constructing the Json
     */
    jsonhl::Value parse();
    /**
     * @brief Empties the buffer (used for performance) -> Does nothing if the buffer is already empty
     *        resets also _index to 0
     *
     */
    void unload();
    /**
     * @brief Fills the buffer expects the buffer to be already checked
     *
     */
    void loadBuffer(std::string &buffer);
};

}; // namespace jsonhl
