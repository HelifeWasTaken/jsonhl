/**
 * File              : ValueUtil.cpp
 * Author            : Mattis Dalleau <mattis.dalleau@epitech.eu>
 * Date              : 09.06.2021
 * Last Modified Date: 09.06.2021
 * Last Modified By  : Mattis Dalleau <mattis.dalleau@epitech.eu>
 */

#include "JsonhlValue.hpp"

const char *jsonhl::Value::____MJsonValueToStr(const jsonhl::Value::ValueType &type) const
{
    switch (type)
    {
    case DOUBLE:
        return "float";
    case BOOL:
        return "boolean";
    case STRING:
        return "string";
    case OBJECT:
        return "object";
    case ARRAY:
        return "array";
    case JSONNULL:
        return "null";
    }
    return "N/A";
}
