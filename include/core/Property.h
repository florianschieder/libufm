namespace libufm
{
    namespace Core
    {
        template <typename T> class ReadOnlyProperty
        {
        public:
            ReadOnlyProperty() {}
            ReadOnlyProperty(T initialValue)
            {
                this->value = initialValue;
            }

            operator T()
            {
                return this->getValue();
            }

        private:
            T getValue()
            {
                return this->value;
            }
        protected:
            T value;
        };

        template <typename T> class Property
            : public ReadOnlyProperty<T>
        {
        public:
            Property()
                : ReadOnlyProperty<T>() {}
            Property(T initialValue)
                : ReadOnlyProperty<T>(initialValue) {}

            void operator=(T newValue)
            {
                this->setValue(newValue);
            }

        private:
            void setValue(T newValue)
            {
                this->value = newValue;
            }
        };
    }
}
