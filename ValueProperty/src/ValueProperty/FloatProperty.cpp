#include "Pch/ntspch.h"
#include "FloatProperty.h"

namespace nkentsuu {
    FloatProperty::FloatProperty() : ValueProperty(0.0f) {}
    FloatProperty::FloatProperty(float value) : ValueProperty(value) {}

    FloatProperty::FloatProperty(const FloatProperty& other) : ValueProperty(other.m_value) {}

    FloatProperty& FloatProperty::operator=(const FloatProperty& other) {
        if (this != &other) {
            m_value = other.m_value;
        }
        return *this;
    }

    FloatProperty& FloatProperty::operator=(float other) {
        if (GetValue() != other) {
            m_value = other;
        }
        return *this;
    }

    std::string FloatProperty::Tostring() {
        return std::to_string(GetValue());
    }

    FloatProperty FloatProperty::operator+(const FloatProperty& other) const {
        return FloatProperty(GetValue() + other.GetValue());
    }

    FloatProperty FloatProperty::operator-(const FloatProperty& other) const {
        return FloatProperty(GetValue() - other.GetValue());
    }

    FloatProperty FloatProperty::operator*(const FloatProperty& other) const {
        return FloatProperty(GetValue() * other.GetValue());
    }

    FloatProperty FloatProperty::operator/(const FloatProperty& other) const {
        if (other.GetValue() != 0.0f) {
            return FloatProperty(GetValue() / other.GetValue());
        } else {
            // Handle division by zero as needed (maybe throw an exception)
            // For simplicity, returning 0 in this example
            return FloatProperty(0.0f);
        }
    }

    bool FloatProperty::operator==(const FloatProperty& other) const {
        return GetValue() == other.GetValue();
    }

    bool FloatProperty::operator!=(const FloatProperty& other) const {
        return !(*this == other);
    }

    FloatProperty& FloatProperty::operator++() {
        SetValue(GetValue() + 1.0f);
        return *this;
    }

    FloatProperty FloatProperty::operator++(int) {
        FloatProperty temp(*this);
        ++(*this);
        return temp;
    }

    FloatProperty& FloatProperty::operator--() {
        SetValue(GetValue() - 1.0f);
        return *this;
    }

    FloatProperty FloatProperty::operator--(int) {
        FloatProperty temp(*this);
        --(*this);
        return temp;
    }

    FloatProperty::operator float() const {
        return GetValue();
    }

    FloatProperty::operator FloatProperty() const {
        return FloatProperty(GetValue());
    }

    FloatProperty& FloatProperty::operator+=(const FloatProperty& other) {
        SetValue(GetValue() + other.GetValue());
        return *this;
    }

    FloatProperty& FloatProperty::operator-=(const FloatProperty& other) {
        SetValue(GetValue() - other.GetValue());
        return *this;
    }

    FloatProperty& FloatProperty::operator*=(const FloatProperty& other) {
        SetValue(GetValue() * other.GetValue());
        return *this;
    }

    FloatProperty& FloatProperty::operator/=(const FloatProperty& other) {
        if (other.GetValue() != 0.0f) {
            SetValue(GetValue() / other.GetValue());
        } else {
            // Handle division by zero as needed (maybe throw an exception)
            // For simplicity, leaving the value unchanged in this example
        }
        return *this;
    }

    FloatProperty& FloatProperty::operator+=(float value) {
        SetValue(GetValue() + value);
        return *this;
    }

    FloatProperty& FloatProperty::operator-=(float value) {
        SetValue(GetValue() - value);
        return *this;
    }

    FloatProperty& FloatProperty::operator*=(float value) {
        SetValue(GetValue() * value);
        return *this;
    }

    FloatProperty& FloatProperty::operator/=(float value) {
        if (value != 0.0f) {
            SetValue(GetValue() / value);
        } else {
            // Handle division by zero as needed (maybe throw an exception)
            // For simplicity, leaving the value unchanged in this example
        }
        return *this;
    }

    void FloatProperty::Receive(void* origin, const std::any& oldValue, const std::any& newValue) {
        ValueProperty::Receive(origin, oldValue, newValue);
    }
}