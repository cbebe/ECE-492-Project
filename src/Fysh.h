#include <ostream>
#include <string_view>

enum class Species {
  FYSH_LITERAL,    // binary scales
  FYSH_IDENTIFIER, // variable
  HEART_MULTIPLY,  // <3 or ♡
  DIVIDE,          // </3 or 💔
  TADPOLE_LT,      // ~o (less than    '<' )
  TADPOLE_GT,      // o~ (greater than '>' )
  TADPOLE_LTE,     // ~o≈ (less than equal to    '<=' )
  TADPOLE_GTE,     // o~≈ (greater than equal to '>=' )
  EQUAL,           // ≈≈  (Equal to '==')
  NOT_EQUAL,       // ~≈  (Not equal to '!=')
  INCREMENT,       // >><fysh> (add 1 'fysh++')
  DECREMENT,       // <fysh><< (sub 1 'fysh--')
  FYSH_TANK_OPEN,  // [ (same as open bracket  '('  )
  FYSH_TANK_CLOSE, // ] (same as closing bracket ')' )
  FYSH_OPEN,       // ><> (same as open curly bracket '{' )
  FYSH_CLOSE,      // <>< (same as closing curly bracket '}' )
  WTF_OPEN,        // WHAT THE FYSH (Throw error opening) ><!@#$>
  WTF_CLOSE,       // WHAT THE FYSH (Throw error closing) <!@#$><
  COMMENT,         // ><//> Comment
  OPENING_COMMENT, // ></*> Comment
  CLOSING_COMMENT, // Comment <*/><

  // TODO bit manipulation
};

class Fysh {
public:
  // PLEASE DELETE THE EXPLINATION COMMENTS WHEN YOU NO LONGER NEED THEM

  // std::string_view
  // https://www.educative.io/answers/what-is-the-cpp-string-view-in-cpp-17
  // std::size_t:
  // https://stackoverflow.com/questions/502856/whats-the-difference-between-size-t-and-int-in-c
  // noexcept: supposed to be faster by saying this function does not throw
  // exceptions std::distance: returns the length when you give a pointer to the
  // start and end of the char array std::move: transfers ownership making the
  // original owner lose its ownership

  // constructors
  /*
  original:
  Fysh (Species in_type) {
    this->type = in_type;
  }

  short version:
    Fysh (Species in_type): type(in_type) {}

  The last curly brackets are for the body but its empty
  */

  //-----------------Constructors---------------------

  // only the Species is given: useful for brackets and stuff since there is
  // only one possible scales
  Fysh(Species inType) noexcept : species{inType} {}

  // Species, pointer to first element in char array and length of char array
  // is given stores the string_view of the element into scales
  Fysh(Species inType, const char *start, std::size_t len) noexcept
      : species{inType}, scales(start, len) {}

  // Species, pointer to start of char array, pointer to end of char array.
  // gets length and stores into string_view
  Fysh(Species inType, const char *start, const char *end) noexcept
      : species{inType}, scales(start, std::distance(start, end)) {}

  // -----------------------METHODS-----------------------
  // This seems hella unoptimized, I'll modify it once we have a testbench
  template <typename... Ts>
  bool isOneOf(Species species1, Species species2, Ts... ks) const noexcept {
    return species == species1 || isOneOf(species2, ks...);
  }

  Species get_species() const noexcept;

  bool isOneOf(Species type1, Species type2) const noexcept;
  std::string_view get_scales() const noexcept;

  bool operator==(const Species &in_species) const noexcept {
    return species == in_species;
  }

  bool operator==(const Fysh &other) const noexcept {
    return other.species == species && other.scales == scales;
  }

private:
  // curly bracker means initialize to default scales (example: 0)
  Species species{};
  std::string_view scales{};
};

std::ostream &operator<<(std::ostream &os, const Fysh &scales);
