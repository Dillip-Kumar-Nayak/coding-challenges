#include <map>
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign( K const& keyBegin, K const& keyEnd, V const& val ) {

    if (!(keyBegin < keyEnd))
        return;

    const auto is_default_value{val == m_valBegin};

    using c_iter = typename std::map<K, V>::const_iterator;
    c_iter upper{};

    const auto upper_bound = m_map.upper_bound(keyEnd);
    if (upper_bound == std::cbegin(m_map)) {
        if (is_default_value) return;
        upper = m_map.insert({keyEnd, m_valBegin}).first;
    } else {
        const auto prev = (upper_bound != std::cbegin(m_map)) ? std::prev(upper_bound) : std::cend(m_map);
        if (prev != std::cend(m_map) && prev->second == val)
            upper = upper_bound;
        else {
            upper = m_map.insert({keyEnd, (prev != std::cend(m_map)) ? prev->second : m_valBegin}).first;
        }
    }

    const auto lower = m_map.lower_bound(keyBegin);
    m_map.erase(lower, upper);

    const auto new_lower = m_map.lower_bound(keyBegin);
    const auto last{new_lower == std::begin(m_map)};
    const auto eq_prev{!m_map.empty() && std::prev(new_lower)->second == val};
    if (last && !is_default_value || !last && !eq_prev)
        m_map.insert({keyBegin, val});


	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};
