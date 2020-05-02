#pragma once

#include "../libufmdef.h"

namespace libufm
{
    namespace Core
    {
        template <typename HolderType, typename ValueType>
        class Property
        {
        public:
            Property()
            {
                this->holder = 0;

                this->OnGetProperty = nullptr;
                this->OnSetProperty = nullptr;
            }

            Property(
                HolderType* holder,
                ValueType(*_OnGetProperty)(HolderType* object))
            {
                this->holder = holder;

                this->OnGetProperty = _OnGetProperty;
            }

            Property(
                HolderType* holder,
                ValueType(*_OnGetProperty)(HolderType* object),
                void (*_OnSetProperty)(HolderType* object, ValueType newValue),
                ValueType initialValue)
            {
                this->holder = holder;

                this->OnGetProperty = _OnGetProperty;
                this->OnSetProperty = _OnSetProperty;

                this->OnSetProperty(this->holder, initialValue);
            }

            Property(
                HolderType* holder,
                ValueType(*_OnGetProperty)(HolderType* object),
                void (*_OnSetProperty)(HolderType* object, ValueType newValue),
                ValueType initialValue,
                bool callSetterAtInitialization)
            {
                this->holder = holder;

                this->OnGetProperty = _OnGetProperty;
                this->OnSetProperty = _OnSetProperty;

                if (callSetterAtInitialization)
                {
                    this->OnSetProperty(this->holder, initialValue);
                }
            }

            void operator=(ValueType newValue)
            {
                if (this->OnSetProperty != nullptr)
                {
                    this->OnSetProperty(this->holder, newValue);
                }
                else
                {
                    throw std::exception("Tried to set a read-only property.");
                }
            }

            operator ValueType()
            {
                return this->OnGetProperty(this->holder);
            }
        
        private:
            HolderType* holder;
            ValueType (*OnGetProperty)(HolderType* object) = nullptr;
            void (*OnSetProperty)(HolderType* object, ValueType newValue) = nullptr;
        };
    }
}
