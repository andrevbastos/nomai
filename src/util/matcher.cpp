#include "nomai/util/matcher.hpp"

namespace nomai {
    Project closestNameMatch(const std::string& target, std::vector<Project> projects) {
        if (projects.empty()) {
            return Project();
        }

        std::vector<Project> bestMatch = { projects[0] };
        float bestScore = -1.0f;
        for (const auto& p : projects) {
            float score = jaroWinklerDistance(target, p.getName());
            
            if (score > bestScore) {
                bestScore = score;
                bestMatch = {p};
            } else if (std::abs(score - bestScore) < 0.0001f) { 
                bestMatch.push_back(p);
            }
        }

        Project result;
        if (bestMatch.size() == 1) {
            result = bestMatch[0];
        } else {
            Project bestRanked = bestMatch[0];
            for (const auto& match : bestMatch) {
                if (match.getRank() > bestRanked.getRank()) {
                    bestRanked = match;
                } else if (match.getRank() == bestRanked.getRank()) {
                    if (match.getLastAccess() > bestRanked.getLastAccess()) {
                        bestRanked = match;
                    }
                }
            }
            result = bestRanked;
        }

        return result;
    };

    Project closestPathMatch(const std::string& target, std::vector<Project> projects) {
        if (projects.empty()) {
            return Project();
        }

        std::vector<Project> bestMatch = { projects[0] };
        float bestScore = -1.0f;
        for (const auto& p : projects) {
            float score = jaroWinklerDistance(target, p.getPath());
            
            if (score > bestScore) {
                bestScore = score;
                bestMatch = {p};
            } else if (std::abs(score - bestScore) < 0.0001f) { 
                bestMatch.push_back(p);
            }
        }

        Project result;
        if (bestMatch.size() == 1) {
            result = bestMatch[0];
        } else {
            Project bestRanked = bestMatch[0];
            for (const auto& match : bestMatch) {
                if (match.getRank() > bestRanked.getRank()) {
                    bestRanked = match;
                } else if (match.getRank() == bestRanked.getRank()) {
                    if (match.getLastAccess() > bestRanked.getLastAccess()) {
                        bestRanked = match;
                    }
                }
            }
            result = bestRanked;
        }

        return result;
    };
    
    float jaroDistance(const std::string& s1, const std::string& s2) {
        int len1 = s1.length();
        int len2 = s2.length();

        if (len1 == 0 && len2 == 0) return 1;
        
        if (len1 == 0 || len2 == 0) return 0;

        int matchingDistance = std::floor(std::max(len1, len2) / 2) - 1;

        std::vector<bool> matches1(len1, false);
        std::vector<bool> matches2(len2, false);

        float m = 0;

        for (int i = 0; i < len1; i++) {
            int start = std::max(0, i - matchingDistance);
            int end = std::min(i + matchingDistance + 1, len2);

            for (int j = start; j < end; j++) {
                if (!matches2[j] && s1[i] == s2[j]) {
                    matches1[i] = true;
                    matches2[j] = true;
                    m++;
                    break;
                }
            }
        }

        if (m == 0) return 0;

        float t = 0;
        int k = 0;

        for (int i = 0; i < len1; i++) {
            if (matches1[i]) {
                while (!matches2[k]) k++;
                if (s1[i] != s2[k]) t++;
                k++;
            }
        }

        t = t / 2;
        
        float Sj = (1.0f / 3.0f) * ((m / (float)len1) + (m / (float)len2) + ((m - t) / (float)m));
        return Sj;
    };

    float jaroWinklerDistance(const std::string& s1, const std::string& s2) {
        float Sj = jaroDistance(s1, s2);

        int l = 0;
        int maxL = 4;
        int minL = std::min((int)s1.length(), (int)s2.length());
        
        for (int i = 0; i < minL; i++) {
            if (s1[i] == s2[i]) {
                l++;
                if (l == maxL) break;
            } else {
                break;
            }
        }

        float p = 0.1f;
        if (Sj < 0.7f) {
            return Sj;
        } else {
            return Sj + (l * p * (1 - Sj));
        }
    };
}