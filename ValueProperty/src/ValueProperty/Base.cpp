#include "Pch/ntspch.h"
#include "Base.h"

namespace nkentsuu {
    std::any ValueProperty::Get() const { return m_value; }

    void ValueProperty::Set(const std::any& value) {
        std::any oldValue = m_value;

        m_value = value;

        // Signal value changed to observers
        SignalValueChanged(&ValueProperty::Receive, oldValue, m_value);
    }

    void ValueProperty::AddObserver(const ValueChange& handler) {
        m_Observers.push_back(handler);
    }

    void ValueProperty::Connect(ValueProperty& other) {
        AddObserver(I_RECEIVE(ValueProperty::Receive, other));
        other.AddObserver(I_TRANSMIT(ValueProperty::Receive));
    }

    void ValueProperty::RemoveObserver(const ValueChange& handler) {
        m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), handler), m_Observers.end());
    }

    void ValueProperty::Disconnect(ValueProperty& other) {
        RemoveObserver(I_RECEIVE(ValueProperty::Receive, other));
        other.RemoveObserver(I_TRANSMIT(ValueProperty::Receive));
    }

    void ValueProperty::SignalValueChanged(void* valuchange, const std::any& oldValue, const std::any& newValue) {
        for (auto& handler : m_Observers) {
            if (static_cast<ValueChange>(valuchange) == handler) continue;

            handler(&ValueProperty::Receive, oldValue, newValue);
        }
    }

    void ValueProperty::Receive(void* origin, const std::any& oldValue, const std::any& newValue) {
        std::any oldValue_ = m_value;

        m_value = newValue;

        SignalValueChanged(origin, oldValue_, m_value);
    }
}