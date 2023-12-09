#ifndef __FLOAT_PROPERTY_H_HEADER__
#define __FLOAT_PROPERTY_H_HEADER__

#pragma once

#include "Base.h"
#include <istream>

namespace nkentsuu {

    class FloatProperty : public ValueProperty {
        public:
        // Constructors
        FloatProperty();
        FloatProperty(float value);

        // Copy constructor
        FloatProperty(const FloatProperty& other);

        // Assignment operator
        FloatProperty& operator=(const FloatProperty& other);

        // Assignment operator
        FloatProperty& operator=(float other);

        // Override GetType to return the type of the property
        VALUE_CONSTRUCT_DATA(float)

        // Override Tostring to return a string representation of the float value
        std::string Tostring() override;

        // Addition operator
        FloatProperty operator+(const FloatProperty& other) const;

        // Subtraction operator
        FloatProperty operator-(const FloatProperty& other) const;

        // Multiplication operator
        FloatProperty operator*(const FloatProperty& other) const;

        // Division operator
        FloatProperty operator/(const FloatProperty& other) const;

        // Comparison operators
        bool operator==(const FloatProperty& other) const;

        bool operator!=(const FloatProperty& other) const;

        // Increment and Decrement operators
        FloatProperty& operator++();

        FloatProperty operator++(int);

        FloatProperty& operator--();

        FloatProperty operator--(int);

        // Conversion operator to float
        operator float() const;

        // Conversion operator from float
        operator FloatProperty() const;

        // Input operator
        friend std::istream& operator>>(std::istream& is, FloatProperty& floatProp) {
            float value;
            is >> value;
            floatProp.SetValue(value);
            return is;
        }

        // Output operator
        friend std::ostream& operator<<(std::ostream& os, const FloatProperty& floatProp) {
            os << floatProp.GetValue();
            return os;
        }

        // Operateur d'ajout en place (+=)
        FloatProperty& operator+=(const FloatProperty& other);

        // Operateur de soustraction en place (-=)
        FloatProperty& operator-=(const FloatProperty& other);

        // Operateur de multiplication en place (*=)
        FloatProperty& operator*=(const FloatProperty& other);

        // Operateur de division en place (/=)
        FloatProperty& operator/=(const FloatProperty& other);

        // Opeérateur d'ajout en place avec un float (+=)
        FloatProperty& operator+=(float value);

        // Operateur de soustraction en place avec un float (-=)
        FloatProperty& operator-=(float value);

        // Operateur de multiplication en place avec un float (*=)
        FloatProperty& operator*=(float value);

        // Operateur de division en place avec un float (/=)
        FloatProperty& operator/=(float value);

        protected:
        // Override receive to handle the specific behavior when connected to another FloatProperty
        void Receive(void* origin, const std::any& oldValue, const std::any& newValue) override;
    };

} // namespace nkentsuu

#endif /* __FLOAT_PROPERTY_H_HEADER__ */
