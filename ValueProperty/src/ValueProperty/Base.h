/**
* @file base.h
* @brief Contains the definition of the ValueProperty class and related macros.
*
* This file provides the implementation of the ValueProperty class, which represents a property with a value that can be observed and changed.
* It also defines macros for constructing data types and binding methods for transmitting and receiving value changes.
*
* @author TEUGUIA TADJUIDJE Rodolf Sederis
* @date 07/12/2023
*/

#ifndef __BASE_H_HEADER__
#define __BASE_H_HEADER__

#pragma once

#include <any>
#include <vector>
#include <functional>
#include <memory>
#include <string>
#include <Platform/Types.h>

namespace nkentsuu {
    // Define a type alias for the ValueChange function
    using ValueChange = std::function<void(void*, const std::any&, const std::any&)>;

    // Macro to construct the data type
    #define VALUE_CONSTRUCT_DATA(type) virtual std::string GetType() override {return #type;}\
                                        virtual type GetValue() const { return std::any_cast<type>(Get()); }\
                                        virtual void SetValue(type value) {SetValue(value);}

    // Placeholder macro for std::bind
    #define PHD(i) std::placeholders::_##i

    // Macro to bind a method for transmitting value changes
    #define I_TRANSMIT(method_) std::bind(&method_, this, PHD(1), PHD(2), PHD(3))

    // Macro to bind a method for receiving value changes
    #define I_RECEIVE(method_, object_) std::bind(&method_, &object_, PHD(1), PHD(2), PHD(3)) 


    class NKENTSUU_API ValueProperty {
        public:
        // Default constructor
        ValueProperty() {}

        // Constructor with initial value
        ValueProperty(const std::any& value) : m_value(value) {}

        // Virtual function to get the type of the value property
        virtual std::string GetType() = 0;

        // Get the current value
        std::any Get() const;

        // Set a new value
        void Set(const std::any& value);

        // Add an observer to the value property
        void AddObserver(const ValueChange& handler);

        // Connect two value properties so that they receive updates from each other
        void Connect(ValueProperty& other);

        // Remove an observer from the value property
        void RemoveObserver(const ValueChange& handler);

        // Disconnect two connected value properties
        void Disconnect(ValueProperty& other);

        // Virtual function to convert the value property to a string representation
        virtual std::string Tostring() = 0;

        protected:
        // Signal that the value has changed to all observers except the origin
        void SignalValueChanged(ValueChange valuchange, const std::any& oldValue, const std::any& newValue);

        // Receive a value change from another value property
        virtual void Receive(void* origin, const std::any& oldValue, const std::any& newValue);

        protected:
        std::any m_value;

        private:
        std::vector<ValueChange> m_Observers;
    };

} // namespace nkentsuu

#endif /* __BASE_H_HEADER__ */
