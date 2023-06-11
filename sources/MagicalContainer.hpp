#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cmath>
using namespace std;

namespace ariel
{
    class MagicalContainer
    {
    private:
        vector<int> container;
        vector<int *> prime_container;
        size_t container_size;
        size_t prime_size;

        // Helper function to check if a number is prime
        bool static isPrime(int num) 
        {
            if (num <= 1)
            {
                return false;
            }
            for (int i = 2; i <= sqrt(num); i++)
            {
                if (num % i == 0)
                {
                    return false;
                }
            }
            return true;
        }

    public:
        MagicalContainer() : container_size(0), prime_size(0)
        {
        }

        // Copy constructor
        MagicalContainer(const MagicalContainer &other) : container(other.container), container_size(other.container_size),
                                                          prime_container(other.prime_container), prime_size(other.prime_size)

        {
        }

        // Destructor
        ~MagicalContainer()
        {
            for (int *it : prime_container)
            {
                delete it;
            }
            // for (auto it : container)
            // {
            //     delete *it;
            // }
        }

        // Add an element to the container
        void addElement(int element)
        {
            // Insert element at the correct position in the container
            vector<int>::iterator it = container.begin();
            while (it != container.end() && *it < element)
            {
                ++it;
            }
            container.insert(it, element);
            container_size++;

            // Check if the element is prime
            bool is_prime = isPrime(element);
            // Insert prime element at the correct position in the prime_container if the number is prime
            if (is_prime)
            {
                int *ptr = new int(element);
                vector<int *>::iterator prime_iterator = prime_container.begin();
                while (prime_iterator != prime_container.end() && **prime_iterator < element)
                {
                    ++prime_iterator;
                }
                prime_container.insert(prime_iterator, ptr);
                prime_size++;
            }
        }

        // Remove an element from the container
        void removeElement(int element)
        {
            vector<int>::iterator position = find(container.begin(), container.end(), element);

            if (position != container.end())
            {
                // element is found - delete it , decrease counter
                container.erase(position);
                container_size--;

                // Vlidate if element is prime
                if (isPrime(element))
                {
                    // if yes - find it and delete it from prime vector
                    vector<int *>::iterator prime_position = find(prime_container.begin(), prime_container.end(), &element);
                    prime_container.erase(prime_position);
                    prime_size--;
                }
            }
            else
            {
                throw runtime_error("Element is not existed in container");
            }
        }

        // Assignment operator
        MagicalContainer &operator=(const MagicalContainer &other)
        {
            if (this != &other)
            {
                container = other.container;
                container_size = other.container_size;
                prime_container = other.prime_container;
                prime_size = other.prime_size;
            }
            return *this;
        }

        // Get the size of the container
        size_t size() const
        {
            return container_size;
        }
        class AscendingIterator
        {
        private:
            MagicalContainer *magic_container;
            size_t current_iterator;
            size_t container_size;

        public:
            AscendingIterator(MagicalContainer &mag_con) : magic_container(&mag_con), current_iterator(0), container_size(mag_con.container.size())
            {
            }

            // Copy constructor
            AscendingIterator(const AscendingIterator &other) : magic_container(other.magic_container), current_iterator(other.current_iterator), container_size(other.container_size)
            {
            }

            // Destructor
            ~AscendingIterator()
            {
            }

            AscendingIterator begin()
            {
                return AscendingIterator(*magic_container);
            }
            AscendingIterator end()
            {
                AscendingIterator it(*magic_container);
                it.current_iterator = magic_container->container_size;
                return it;
            }

            // Assignment operator
            AscendingIterator &operator=(const AscendingIterator &other)
            {
                if (magic_container != other.magic_container)
                {
                    throw std::runtime_error("Iterators are pointing to different containers");
                }

                if (this != &other)
                {
                    magic_container = other.magic_container;
                    current_iterator = other.current_iterator;
                }

                return *this;
            }

            // Equality operator
            bool operator==(const AscendingIterator &other) const
            {
                return magic_container == other.magic_container && current_iterator == other.current_iterator;
            }
            bool operator!=(const AscendingIterator &other) const
            {
                return !(*this == other);
            }

            // Greater than operator
            bool operator>(const AscendingIterator &other) const
            {
                return magic_container == other.magic_container && current_iterator > other.current_iterator;
            }
            bool operator<(const AscendingIterator &other) const
            {
                return magic_container == other.magic_container && current_iterator < other.current_iterator;
            }

            // Reference operator
            int operator*() const
            {
                return magic_container->container[current_iterator];
            }

            // increment operator
            AscendingIterator &operator++()
            {
                if (current_iterator == magic_container->container_size)
                {
                    throw std::runtime_error("Cannot increment iterator beyond the container size");
                }
                ++current_iterator;
                return *this;
            }
        };

        class SideCrossIterator
        {
        private:
            MagicalContainer *magic_container;
            size_t current_iterator;

        public:
            SideCrossIterator(MagicalContainer &container) : magic_container(&container), current_iterator(0)
            {
            }

            // Copy constructor
            SideCrossIterator(const SideCrossIterator &other) : magic_container(other.magic_container), current_iterator(other.current_iterator)
            {
            }

            // Destructor
            ~SideCrossIterator()
            {
            }

            // Get the iterator to the beginning of the container
            MagicalContainer::SideCrossIterator begin()
            {
                return SideCrossIterator(*magic_container);
            }

            // Get the iterator to the end of the container
            MagicalContainer::SideCrossIterator end()
            {
                SideCrossIterator it(*magic_container);
                it.current_iterator = magic_container->container.size();
                return it;
            }

            // Equality operator
            bool operator==(const SideCrossIterator &other) const
            {
                return magic_container == other.magic_container && current_iterator == other.current_iterator;
            }
            bool operator!=(const SideCrossIterator &other) const
            {
                return !(*this == other);
            }

            // Greater than operator
            bool operator>(const SideCrossIterator &other) const
            {
                return magic_container == other.magic_container && current_iterator > other.current_iterator;
            }
            bool operator<(const SideCrossIterator &other) const
            {
                return magic_container == other.magic_container && current_iterator < other.current_iterator;
            }

            // Reference operator
            int operator*() const
            {
                return (*(magic_container)).container[current_iterator];
            }

            // Increment operator
            MagicalContainer::SideCrossIterator &operator++()
            {
                size_t mid_index = magic_container->container_size / 2;
                if (current_iterator == magic_container->container_size)
                {
                    throw std::runtime_error("Cannot increment iterator beyond the container size");
                }
                if (current_iterator < mid_index) // First half of the vector
                {
                    current_iterator = magic_container->container_size - current_iterator - 1; // Go to the parallel at the other side
                }
                else // Second half og the vector
                {
                    if (current_iterator == mid_index)
                    {
                        current_iterator = magic_container->container_size; // Go to the end
                    }
                    else
                    {
                        current_iterator = magic_container->container_size - current_iterator; // Go to the parallel at the other side
                    }
                }
                return *this;
            }

            // Assignment operator
            SideCrossIterator &operator=(const SideCrossIterator &other)
            {
                if (magic_container != other.magic_container)
                {
                    throw std::runtime_error("Iterators are pointing to different containers");
                }

                if (this != &other)
                {
                    magic_container = other.magic_container;
                    current_iterator = other.current_iterator;
                }

                return *this;
            }
        };

        class PrimeIterator
        {
        private:
            MagicalContainer *magic_container;
            size_t prime_iterator;

        public:
            PrimeIterator(MagicalContainer &container) : magic_container(&container), prime_iterator(0)
            {
                // Find the first prime element in the container
                while (prime_iterator < container.prime_size && !container.isPrime(*container.prime_container[prime_iterator]))
                {
                    ++prime_iterator;
                }
            }

            // Copy constructor
            PrimeIterator(const PrimeIterator &other) : magic_container(other.magic_container), prime_iterator(other.prime_iterator)
            {
            }

            // Destructor
            ~PrimeIterator()
            {
            }

            PrimeIterator begin()
            {
                return *this;
            }
            PrimeIterator end()
            {
                PrimeIterator it(*magic_container);
                it.prime_iterator = magic_container->prime_size;
                return it;
            }

            // Equality operators
            bool operator==(const PrimeIterator &other) const
            {
                return magic_container == other.magic_container && prime_iterator == other.prime_iterator;
            }
            bool operator!=(const PrimeIterator &other) const
            {
                return !(*this == other);
            }

            // Greater than operator
            bool operator>(const PrimeIterator &other) const
            {
                return magic_container == other.magic_container && prime_iterator > other.prime_iterator;
            }
            bool operator<(const PrimeIterator &other) const
            {
                return magic_container == other.magic_container && prime_iterator < other.prime_iterator;
            }

            // Reference operator
            int operator*() const
            {
                return *magic_container->prime_container[prime_iterator];
            }

            // Assignment operator
            PrimeIterator &operator=(const PrimeIterator &other)
            {
                if (magic_container != other.magic_container)
                {
                    throw runtime_error("Iterators are pointing to different containers");
                }
                
                if (this != &other)
                {
                    magic_container = other.magic_container;
                    prime_iterator = other.prime_iterator;
                }
                return *this;
            }

            // increment operator
            PrimeIterator &operator++()
            {
                if (prime_iterator >= magic_container->prime_size)
                {
                    throw std::runtime_error("Cannot increment iterator beyond the container size");
                }

                ++prime_iterator;
                // Find the next prime element in the container
                while (prime_iterator < magic_container->prime_size && !magic_container->isPrime(*magic_container->prime_container[prime_iterator]))
                {
                    ++prime_iterator;
                }

                return *this;
            }
        };
    };

}
