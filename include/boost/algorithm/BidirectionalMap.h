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
            // �ڲ�ʹ������ӳ��
            std::unordered_map<int, std::string> index_to_name;
            std::unordered_map<std::string, int> name_to_index;

        public:
            // ���ӳ��
            void AddMapping(int index, const std::string& name) {
                // ����Ƿ��Ѿ����ڳ�ͻ��ӳ��
                if (index_to_name.count(index) > 0 || name_to_index.count(name) > 0) {
                    throw std::runtime_error("Mapping already exists for the given index or name.");
                }

                // ���˫��ӳ��
                index_to_name[index] = name;
                name_to_index[name] = index;
            }

            // ͨ��������������
            std::string GetName(int index) const {
                if (index_to_name.count(index) == 0) {
                    throw std::runtime_error("Index not found.");
                }
                return index_to_name.at(index);
            }

            // ͨ�����ֲ�������
            int GetIndex(const std::string& name) const {
                if (name_to_index.count(name) == 0) {
                    throw std::runtime_error("Name not found.");
                }
                return name_to_index.at(name);
            }

            // ɾ��ӳ�䣨ͨ��������
            void RemoveByIndex(int index) {
                if (index_to_name.count(index) == 0) {
                    throw std::runtime_error("Index not found.");
                }
                std::string name = index_to_name[index];
                index_to_name.erase(index);
                name_to_index.erase(name);
            }

            // ɾ��ӳ�䣨ͨ�����֣�
            void RemoveByName(const std::string& name) {
                if (name_to_index.count(name) == 0) {
                    throw std::runtime_error("Name not found.");
                }
                int index = name_to_index[name];
                name_to_index.erase(name);
                index_to_name.erase(index);
            }

            // ��������Ƿ����
            bool IndexExists(int index) const {
                return index_to_name.count(index) > 0;
            }

            // ��������Ƿ����
            bool NameExists(const std::string& name) const {
                return name_to_index.count(name) > 0;
            }

            // ��ӡ����ӳ�䣨���ڵ��ԣ�
            void PrintMappings() const {
                for (const auto& [index, name] : index_to_name) {
                    std::cout << "Index: " << index << " -> Name: " << name << std::endl;
                }
            }
        };
    }
}

