#include <iostream>

enum class States : std::int32_t
{
	START = 0,
	INTEGER = 1,
	BETWEEN = 2,
	DECIMAL = 3,
	UNKNOWN = 4
};

template <typename Enumeration>
constexpr std::enable_if_t<std::is_enum<Enumeration>::value,
std::underlying_type_t<Enumeration>> as_int(const Enumeration value)
{
	return static_cast<std::underlying_type_t<Enumeration>>(value);
}

bool VerifyValidNumber(std::string num)
{
	States state(States::START);

	for (auto& c : num)
	{
		switch (state)
		{
		case States::START:
		case States::INTEGER:
			switch (c)
			{
			case '.':
				state = States::BETWEEN;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '9':
				state = States::INTEGER;
				break;
			default:
				state = States::UNKNOWN;
				break;
			}
			break;
		case States::BETWEEN:
			switch (c)
			{
			case '.':
				state = States::UNKNOWN;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '9':
				state = States::DECIMAL;
				break;
			default:
				state = States::UNKNOWN;
				break;
			}
			break;
		case States::DECIMAL:
			switch (c)
			{
			case '.':
				state = States::UNKNOWN;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '9':
				state = States::DECIMAL;
				break;
			default:
				state = States::UNKNOWN;
				break;
			}
			break;
		case States::UNKNOWN:
			state = States::UNKNOWN;
			break;
		default:
			state = States::UNKNOWN;
			break;
		}
	}

	if (state == States::UNKNOWN || state == States::BETWEEN)
		return false;
	else
		return true;
}

int main_StateMachine()
{
	std::string num("22.");

	while (true)
	{
		std::cin >> num;
		if (VerifyValidNumber(num))
			std::cout << "Valid\n";
		else
			std::cout << "Not valid\n";
	}
	return 0;
}