#pragma once
#include <vector>

template <typename Data, typename Classification>
class TrainingData {
public:
    struct CategorizedData {
        Data data;
        Classification classification;
    };
    explicit TrainingData(const std::vector<CategorizedData>& categorizedData) : categorizedData(categorizedData) {};

private:
    const std::vector<CategorizedData>& categorizedData;
};
