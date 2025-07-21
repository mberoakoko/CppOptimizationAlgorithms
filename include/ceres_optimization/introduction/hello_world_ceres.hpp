//
// Created by mbero on 21/07/2025.
//

#ifndef HELLO_WORLD_CERES_HPP
#define HELLO_WORLD_CERES_HPP
#include <bits/stdc++.h>
#include "ceres/ceres.h"
#include <glog/logging.h>

namespace tutorial_ceres::introduction {

    inline auto cost_functor = []<typename T>(const T* const x, T* residual) -> bool{
        residual[0] = 10 - x[0];
        return true;
    };

    struct CostFunctor {
        ~CostFunctor() {
            std::cout << "Deleter was called " << std::endl;
        }
        template <typename T>
        auto operator()(const T* const x, T* residual) const -> bool {
            residual[0] = 10.0 - x[0];
            return true;
        }
    };

    using MyDynamicAutoDiffCostFunction =  ceres::DynamicAutoDiffCostFunction<decltype(cost_functor)>;
    using ClassicalCostFunction = ceres::AutoDiffCostFunction<CostFunctor, 1, 1>;

    inline auto hello_world_ceres_runner() -> void {
        double x_initial = 5.0;
        double x = x_initial;

        ceres::Problem problem;
        CostFunctor* cost_functor_obj = new CostFunctor{};
        ceres::CostFunction* cost_function = new ClassicalCostFunction(new CostFunctor{});
        problem.AddResidualBlock(cost_function, nullptr, &x);
        ceres::Solver::Options options {
            .linear_solver_type = ceres::DENSE_QR,
            .minimizer_progress_to_stdout = true,
        };
        ceres::Solver::Summary summary;
        ceres::Solver solver;
        solver.Solve(options, &problem, &summary);
        std::cout << "\033[0;32m"<< std::endl;
        std::cout << summary.BriefReport() << std::endl;
        std::cout << "\033[0m"<< std::endl;

    };

    inline auto hello_world_ceres_runner_no_unique() -> void {
        constexpr double x_initial = 5.0;
        double x = x_initial;

        ceres::Problem problem;
        auto cost_raw = new ClassicalCostFunction(CostFunctor{});
        problem.AddResidualBlock(cost_raw, nullptr, &x);

        ceres::Solver::Options options {
            .linear_solver_type = ceres::DENSE_QR,
            .minimizer_progress_to_stdout = true,
        };

        ceres::Solver::Summary summary;
        ceres::Solve(options, &problem, &summary);

        delete cost_raw;
    }

    inline auto hello_world_ceres_runner_but_idomatic() {
        constexpr double x_initial = 5.0;
        double x = x_initial;

        ceres::Problem problem;
        auto cost_functor = std::make_unique<CostFunctor>();
        auto cost_function = std::make_unique<ClassicalCostFunction>(cost_functor.release());
        problem.AddResidualBlock(cost_function.release(), nullptr, &x);

        ceres::Solver::Options options {
            .linear_solver_type = ceres::DENSE_QR,
            .minimizer_progress_to_stdout = true,
        };
        ceres::Solver::Summary summary;
        ceres::Solver solver;
        solver.Solve(options, &problem, &summary);
        std::cout << "\033[0;32m"<< std::endl;
        std::cout << summary.BriefReport() << std::endl;
        std::cout << "\033[0m"<< std::endl;


    }
}

#endif //HELLO_WORLD_CERES_HPP
