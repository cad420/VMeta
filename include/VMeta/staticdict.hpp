#pragma once

#include <memory>
#include <type_traits>

#include <VMeta/operation.hpp>

namespace vm
{

	namespace detail
	{
		struct NullType;
		template<size_t N, template<typename...> class ContType, typename ...ValType>
		struct CreateImpl
		{
			using Type = typename CreateImpl<N - 1, ContType, NullType, ValType...>::Type;

		};

		template<template<typename ...> class ContType, typename ...ValType>
		struct CreateImpl<0, ContType, ValType...>
		{
			using Type = ContType<ValType...>;
		};

		template<typename ValType,
			size_t N,
			size_t M,
			typename Ty1,
			typename ...Ty2>
			struct NewTupleTypeImpl;

		template<typename ValType,
		size_t N,
		size_t M,
		template<typename...> class ContType,
		typename... Ty1,
		typename Ty,
		typename... Ty2>
		struct NewTupleTypeImpl<ValType,N,M,ContType<Ty1...>,Ty,Ty2...>
		{
			using Type = typename NewTupleTypeImpl<ValType, N, M + 1, ContType<Ty1..., Ty>, Ty2...>::Type;
		};

		template<typename ValType,size_t N,template<typename...> class ContType,
		typename... Ty1,typename Ty,typename... Ty2>
		struct NewTupleTypeImpl<ValType,N,N,ContType<Ty1...>,Ty,Ty2...>
		{
			using Type = ContType<Ty1..., ValType, Ty2...>;
		};
		template<typename ValType,size_t pos,typename ContType,typename... Ty>
		using NewTupleType =typename  NewTupleTypeImpl<ValType, pos, 0, ContType, Ty...>::Type;
		
	}



	template<typename...Args>
	class StaticDict
	{
		template<typename ...ValTypes>
		struct Value
		{
			Value() = default;

			Value(std::shared_ptr<void>(&& input)[sizeof...(ValTypes)])
			{
				for(size_t i =0;i<sizeof...(ValTypes);i++)
				{
					tuple[i] = std::move(input[i]);
				}
			}
			template<typename KeyType, typename ValType>
			auto Set(ValType&& val)&&
			{
				constexpr static size_t pos = FindFirstIndexOf<KeyType, Args...>;
				using DecayValType =typename std::decay<ValType>::type;

				tuple[pos] = std::shared_ptr<void>(new DecayValType(std::forward<ValType>(val)),
					[](void* ptr)
					{
						delete static_cast<DecayValType*>(ptr);
					}
				);

				return detail::NewTupleType<DecayValType, pos, Value<>, ValTypes...>(std::move(tuple));

			}

			template<typename KeyType>
			const auto & Get()const
			{
				constexpr size_t pos = FindFirstIndexOf<KeyType, Args...>;
				using Ty = GetTypeOf<pos, ValTypes...>;
				return *(static_cast<Ty*>(tuple[pos].get()));
			}

		private:
			std::shared_ptr<void> tuple[sizeof...(ValTypes)];
		};
	public:
		static auto Create()
		{
			using namespace detail;
			using Ty= typename CreateImpl<sizeof...(Args), Value>::Type;
			return Ty{};
		}
	};
}