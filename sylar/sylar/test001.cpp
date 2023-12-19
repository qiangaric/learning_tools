#include <iostream>
#include <random>

double monte_carlo_pi(int num_samples)
{
    int inside_circle = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < num_samples; ++i)
    {
        double x = dis(gen);
        double y = dis(gen);

        double distance = x * x + y * y;

        if (distance <= 1)
        {
            inside_circle++;
        }
    }

    double pi_estimate = (static_cast<double>(inside_circle) / num_samples) * 4;
    return pi_estimate;
}

int main()
{
    // 设置模拟次数
    int num_samples = 1000000;

    // 运行蒙特卡洛模拟
    double estimated_pi = monte_carlo_pi(num_samples);

    // 打印结果
    std::cout << "Estimated value of pi using " << num_samples << " samples: " << estimated_pi << std::endl;

    return 0;
}
