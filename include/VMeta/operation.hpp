
namespace vm
{

	// Add
	template<int v1,int v2>
	constexpr int Add = v1 + v2;

	template<typename Ty>
	struct Identity {
		using Type = Ty;
	};


	// CountOnes
	template<size_t v>
	constexpr size_t CountOnes = (v % 2) + CountOnes<v / 2>;

	template<>
	constexpr size_t CountOnes<0> = 0;

	// Sum
	template<int...v>
	constexpr int Sum = 0;
	
	template<int v1,int...v2>
	constexpr int Sum<v1, v2...> = v1 + Sum<v2...>;

	//
	// FindFirstIndexOf
	template<typename TargetType,size_t N,typename CurType,typename ... Ty>
	struct FindFirstIndexOfImpl
	{
		constexpr static size_t Value = FindFirstIndexOfImpl<TargetType, N + 1, Ty...>::Value;
	};

	template<typename TargetType,size_t N,typename ...Ty>
	struct FindFirstIndexOfImpl<TargetType,N,TargetType,Ty...>
	{
		constexpr static size_t Value = N;
	};

	template<typename TargetType,typename ...Args>
	constexpr size_t FindFirstIndexOf = FindFirstIndexOfImpl<TargetType, 0, Args...>::Value;


	//GetTypeOf

	template<size_t Pos,typename ...Ty>
	struct GetTypeOfImpl
	{
		static_assert(Pos != 0, "invalid position");
	};

	template<size_t Pos,typename CurType,typename ...Ty>
	struct GetTypeOfImpl<Pos,CurType,Ty...>
	{
		using Type =typename std::conditional < (Pos == 0), Identity<CurType>,GetTypeOfImpl<Pos - 1, Ty...>>::type::Type;
	};

	template<size_t Pos,typename ...Ty>
	using GetTypeOf = typename GetTypeOfImpl<Pos, Ty...>::Type;
	
}