//
// Created by mbero on 18/07/2025.
//

#ifndef BASE_ELEMENTS_HPP
#define BASE_ELEMENTS_HPP

#include <functional>
#include <variant>

#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
namespace Optim::base {
    template<typename T>
    using VectorType = xt::xarray<T>;

    using VectorType_d = VectorType<double>;
    using VectorType_f = VectorType<float>;
    using VectorType_i = VectorType<int>;

    using VectorVar = std::variant<VectorType_d, VectorType_f, VectorType_i>;
    using InputType = std::variant<VectorVar, double>;
    using OutputType = std::variant<VectorVar, double>;

    using FuncType = std::function<OutputType(InputType)>;
}

namespace Optim::diff {

    template<class... Ts>
    struct overloads : Ts... { using Ts::operator()...; };

    struct ForwardDiff{};
    struct BackWardDiff{};
    struct CentralDiff{};

    template<typename T>
    concept ValidDiffTag = std::same_as<T, ForwardDiff> || std::same_as<T, BackWardDiff> || std::same_as<T, CentralDiff>;

    namespace details_ {
        constexpr auto visitor_ = overloads {
            [](base::VectorType_d&  val) -> base::VectorType_d&{ return val;},
            [](base::VectorType_f&  val) -> base::VectorType_f&{ return val;},
            [](base::VectorType_i&  val)-> base::VectorType_i&{ return val;},
        };

        constexpr auto const_visitor_ = overloads{
            [](const base::VectorType_d&  val) -> const base::VectorType_d&{ return val;},
            [](const base::VectorType_f&  val) -> const base::VectorType_f&{ return val;},
            [](const base::VectorType_i&  val)-> const base::VectorType_i&{ return val;},
        };
    }


    class Diff {
        static void forward_diff_impl(const base::FuncType& func, const base::InputType& x, const base::InputType& h) -> base::OutputType {
            if (std::holds_alternative<float>(x) and std::holds_alternative<float>(h)) {
                const auto x_ = std::get<double>(x) ;
                const auto h_ = std::get<double>(h);
                return (1/h_) * (func(x_ + h_) - func(x_));
            }
            const base::VectorType_d x_ = std::visit(details_::const_visitor_, std::get<base::VectorVar>(x));
            const base::VectorType_d h_ = std::visit(details_::const_visitor_, std::get<base::VectorVar>(h));
            return func(h_);
        };

        static void backward_diff_impl(const base::FuncType& func, const base::InputType& x, const base::InputType& h) -> base::OutputType {
            if (std::holds_alternative<float>(x) and std::holds_alternative<float>(h)) {
                const auto x_ = std::get<double>(x) ;
                const auto h_ = std::get<double>(h);
                return (1/h_) * (func(x_ + h_) - func(x_));
            }
            const base::VectorType_d x_ = std::visit(details_::const_visitor_, std::get<base::VectorVar>(x));
            const base::VectorType_d h_ = std::visit(details_::const_visitor_, std::get<base::VectorVar>(h));
            return func(h_);
        }

        static void central_diff_impl(const base::FuncType& func, const base::InputType& x, const base::InputType& h) -> base::OutputType {
            if (std::holds_alternative<float>(x) and std::holds_alternative<float>(h)) {
                const auto x_ = std::get<double>(x) ;
                const auto h_ = std::get<double>(h);
                return (1/h_) * (func(x_ + h_) - func(x_));
            }
            const base::VectorType_d x_ = std::visit(details_::const_visitor_, std::get<base::VectorVar>(x));
            const base::VectorType_d h_ = std::visit(details_::const_visitor_, std::get<base::VectorVar>(h));
            return func(h_);
        }

        static void dispatcher(const ForwardDiff tag, const base::FuncType& func, const base::InputType& x, const base::InputType& h) -> base::OutputType {
            static_cast<void>(tag);
            return forward_diff_impl(func, x, h);
        };

        static void dispatcher(const BackWardDiff& tag, const base::FuncType& func, const base::InputType& x, const base::InputType& h) -> base::OutputType {
            static_cast<void>(tag);
            return backward_diff_impl(func, x, h);
        }

        static void dispatcher(const CentralDiff& tag, const base::FuncType& func, const base::InputType& x, const base::InputType& h) -> base::OutputType {
            static_cast<void>(tag);
            return central_diff_impl(func, x, h);
        }
    public:
        template<ValidDiffTag Tag>
        static auto eval(const base::FuncType& func, const base::InputType& x, const base::InputType& h) -> base::OutputType {
            return dispatcher(Tag{}, func, x, h);
        };
    };
}

#endif //BASE_ELEMENTS_HPP
