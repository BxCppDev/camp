// <insert copyright>

#ifndef CAMP_ENUM_HPP
#define CAMP_ENUM_HPP


#include <camp/config.hpp>
#include <camp/enumbuilder.hpp>
#include <camp/detail/enummanager.hpp>
#include <camp/detail/typeid.hpp>
#include <boost/noncopyable.hpp>
#include <string>
#include <vector>


namespace camp
{
/**
 * \brief camp::Enum represents a metaenum composed of <name, value> pairs
 *
 * Enums are declared, bound to a C++ type and filled with the \c declare
 * template function.
 *
 * \code
 * enum MyEnum {one = 1, two = 2, ten = 10};
 *
 * camp::Enum::declare<MyEnum>("MyEnum")
 *     .value("one", one)
 *     .value("two", two)
 *     .value("ten", ten);
 * \endcode
 *
 * It then provides a set of accessors to retrieve names, values and pairs contained in it.
 *
 * \code
 * const camp::Enum& metaenum = camp::enumByType<MyEnum>();
 *
 * bool b1 = metaenum.hasName("one");     // b1 == true
 * bool b2 = metaenum.hasValue(5);        // b2 == false
 *
 * std::string s = metaenum.name(10);     // s == "ten"
 * long l = metaenum.value("two");        // l == 2
 *
 * camp::Enum::Pair p = metaenum.pair(0); // p == {"one", one}
 * \endcode
 *
 * \remark All values and names are unique within the metaenum.
 *
 * \sa Class, EnumBuilder
 */
class Enum : boost::noncopyable
{
public:

    /**
     * \brief Structure defining the <name, value> pairs stored in metaenums
     */
    struct Pair
    {
        std::string name; ///< Name of the pair
        long value; ///< Value of the pair
    };

public:

    /**
     * \brief Declare a new metaenum
     *
     * This is the function to call to create a new metaenum. The template
     * parameter T is the C++ enum type that will be bound to the metaclass.
     *
     * \param name Name of the metaenum in CAMP. This name identifies
     *             the metaenum and thus has to be unique
     *
     * \return A EnumBuilder object that will provide functions
     *         to fill the new metaenum with values.
     */
    template <typename T>
    static EnumBuilder declare(const std::string& name);

    /**
     * \brief Return the name of the metaenum
     *
     * \return String containing the name of the metaenum
     */
    CAMP_API const std::string& name() const;

    /**
     * \brief Return the size of the metaenum
     *
     * \return Total number of values contained in the metaenum
     */
    CAMP_API std::size_t size() const;

    /**
     * \brief Get a pair by its index
     *
     * \param index Index of the pair to get
     *
     * \return index-th pair
     *
     * \throw InvalidIndex index is out of range
     */
    CAMP_API const Pair& pair(std::size_t index) const;

    /**
     * \brief Check if the enum contains a name
     *
     * \param name Name to check
     *
     * \return True if the metaenum contains a pair whose name is \a name
     */
    CAMP_API bool hasName(const std::string& name) const;

    /**
     * \brief Check if the enum contains a value
     *
     * \param value Value to check
     *
     * \return True if the metaenum contains a pair whose value is \a value
     */
    CAMP_API bool hasValue(long value) const;

    /**
     * \brief Return the name corresponding to given a value
     *
     * \param value Value to get
     *
     * \return Name of the requested value
     *
     * \throw InvalidEnumValue value doesn't exist in the metaenum
     */
    CAMP_API const std::string& name(long value) const;

    /**
     * \brief Return the value corresponding to given a name
     *
     * \param name Name to get
     *
     * \return Value of the requested name
     *
     * \throw InvalidEnumName name doesn't exist in the metaenum
     */
    CAMP_API long value(const std::string& name) const;

    /**
     * \brief Operator == to check equality between two metaenums
     *
     * Two metaenums are equal if their name is the same.
     *
     * \param other Metaenum to compare with this
     *
     * \return True if both metaenums are the same, false otherwise
     */
    CAMP_API bool operator==(const Enum& other) const;

    /**
     * \brief Operator != to check inequality between two metaenums
     *
     * \param other Metaenum to compare with this
     *
     * \return True if metaenums are different, false if they are equal
     */
    CAMP_API bool operator!=(const Enum& other) const;

private:

    friend class EnumBuilder;
    friend class detail::EnumManager;

    /**
     * \brief Construct the metaenum from its name
     *
     * \param name Name of the metaenum
     */
    Enum(const std::string& name);

    typedef std::vector<Pair> PairArray;

    std::string m_name; ///< Name of the metaenum
    PairArray m_pairs; ///< List of pairs stored in the metaenum
};

} // namespace camp

#include <camp/enum.inl>


#endif // CAMP_ENUM_HPP