#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>
// TODO: think
namespace boost {
    namespace algorithm{
        class BidirectionalMap {
        private:
            // 内部使用两个映射
            std::unordered_map<int, std::string> index_to_name;
            std::unordered_map<std::string, int> name_to_index;

        public:
            // 添加映射
            void AddMapping(int index, const std::string& name) {
                // 检查是否已经存在冲突的映射
                if (index_to_name.count(index) > 0 || name_to_index.count(name) > 0) {
                    throw std::runtime_error("Mapping already exists for the given index or name.");
                }

                // 添加双向映射
                index_to_name[index] = name;
                name_to_index[name] = index;
            }

            // 通过索引查找名字
            std::string GetName(int index) const {
                if (index_to_name.count(index) == 0) {
                    throw std::runtime_error("Index not found.");
                }
                return index_to_name.at(index);
            }

            // 通过名字查找索引
            int GetIndex(const std::string& name) const {
                if (name_to_index.count(name) == 0) {
                    throw std::runtime_error("Name not found.");
                }
                return name_to_index.at(name);
            }

            // 删除映射（通过索引）
            void RemoveByIndex(int index) {
                if (index_to_name.count(index) == 0) {
                    throw std::runtime_error("Index not found.");
                }
                std::string name = index_to_name[index];
                index_to_name.erase(index);
                name_to_index.erase(name);
            }

            // 删除映射（通过名字）
            void RemoveByName(const std::string& name) {
                if (name_to_index.count(name) == 0) {
                    throw std::runtime_error("Name not found.");
                }
                int index = name_to_index[name];
                name_to_index.erase(name);
                index_to_name.erase(index);
            }

            // 检查索引是否存在
            bool IndexExists(int index) const {
                return index_to_name.count(index) > 0;
            }

            // 检查名字是否存在
            bool NameExists(const std::string& name) const {
                return name_to_index.count(name) > 0;
            }

            // 打印所有映射（用于调试）
            void PrintMappings() const {
                for (const auto& [index, name] : index_to_name) {
                    std::cout << "Index: " << index << " -> Name: " << name << std::endl;
                }
            }
        };
    }
}

