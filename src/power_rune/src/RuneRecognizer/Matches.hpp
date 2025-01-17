#ifndef MATCHES_HPP
#define MATCHES_HPP
#include "Feature.hpp"


#include <optional>
#include <vector>

static inline const cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::NORM_HAMMING,true);

/**
 * \brief 两个特征间的匹配关系
 */
struct Matches {
    const Feature                &reference; /**< 参考特征 */
    const Feature                &actual;    /**< 实际特征 */
    const std::vector<cv::DMatch> matches;   /**< 匹配关系 */

    /**
     * \brief 获取两个特征之间的匹配关系
     *
     * \param reference 参考特征
     * \param actual 实际特征
     * \return 两个特征间的匹配关系
     */
    [[nodiscard]] static auto between(const Feature &reference, const Feature &actual) -> Matches {
        std::vector<cv::DMatch>              goodMatch;// 存储好的匹配关系
        // std::vector<std::vector<cv::DMatch>> matches;  // 存储所有匹配关系

        // 使用matcher进行knnMatch，得到所有匹配关系
        // matcher->knnMatch(actual.descriptors, reference.descriptors, matches, 2);

        // 遍历所有匹配关系
        // for (std::vector<cv::DMatch> &match: matches)
            // 如果当前匹配关系的第一项距离小于0.7乘以第二项的距离，则认为这是一个好的匹配关系
            // if (match[0].distance < 0.8 * match[1].distance)
                // 将好的匹配关系添加到goodMatch中
                // goodMatch.push_back(match[0]);

        matcher->match(actual.descriptors, reference.descriptors, goodMatch);

        // 返回好的匹配关系以及参考特征和实际特征
        return {reference, actual, move(goodMatch)};
    }
};


#endif //MATCHES_HPP
