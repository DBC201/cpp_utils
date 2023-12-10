#ifndef EXTRAPOLATION_UTILS_H
#define EXTRAPOLATION_UTILS_H

#include <vector>	

namespace cpp_utils::extrapolation_utils {
	template <typename T>
	struct Operation {
		virtual T operate(T a, T b) = 0;
	};

	template <typename T>
	struct Addition: public Operation<T> {
		T operate (T a, T b) override {
			return a + b;
		}
	};

	template <typename T>
	struct Multiplication: public Operation<T> {
		T operate (T a, T b) override {
			return a * b;
		}
	};

	template <typename T>
	struct Division: public Operation<T> {
		T operate (T a, T b) override {
			return a / b;
		}
	};

	template <typename T>
	struct Subtraction: public Operation<T> {
		T operate (T a, T b) override {
			return a - b;
		}
	};

	template <typename T>
	class ExtrapolationUtils {
	public:
		ExtrapolationUtils (std::vector<T>& sequence, std::vector<Operation<T>*>& operations, std::vector<Operation<T>*>& polar_operations) {
			this->operations = operations;
			this->polar_operations = polar_operations;
			populate_layers(sequence, UINT32_MAX);
		}

		ExtrapolationUtils (std::vector<T>& sequence, std::vector<Operation<T>*>& operations, std::vector<Operation<T>*>& polar_operations, uint32_t max_depth) {
			this->operations = operations;
			this->polar_operations = polar_operations;
			populate_layers(sequence, max_depth);
		}

		T extrapolate(int operation_index) {
			T result = layers[operation_index].back().back();
			for (int i=layers[operation_index].size()-2; i>=0; i--) {
				result = operations[operation_index]->operate(result, layers[operation_index][i].back());
			}
			return result;
		}

		template <typename T>
		static std::vector<T> get_next_layer(std::vector<T>& sequence, Operation<T>* operation) {
			if (sequence.size() <= 1) {
				return sequence;
			}
			std::vector<T> next_layer(sequence.size() - 1);
			bool all_the_same = true;
			for (int i=0; i<sequence.size() - 1; i++) {
				next_layer[i] = operation->operate(sequence[i+1], sequence[i]);
				if (i != 0 && next_layer[i] != next_layer[0]) {
					all_the_same = false;
				}
			}
			
			if (all_the_same) {
				return {next_layer[0]};
			}
			else {
				return next_layer;
			}
		}
	private:
		std::vector<std::vector<std::vector<T>>> layers;
		std::vector<Operation<T>*> operations;
		std::vector<Operation<T>*> polar_operations;

		void populate_layers(std::vector<T>& sequence, uint32_t max_depth) {
			layers = std::vector<std::vector<std::vector<T>>>(operations.size(), std::vector<std::vector<T>>(1, std::vector<T>(sequence)));
			uint32_t depth = 0;

			bool all_found = false;

			while (depth < max_depth && !all_found) {
				all_found = true;
				for (int i=0; i<polar_operations.size(); i++) {
					if (layers[i].back().size() > 1) {	
						layers[i].push_back(get_next_layer<T>(layers[i].back(), polar_operations[i]));
						all_found = false;
					}
				}
				depth++;
			}
		}
	};
} // cpp_utils::extrapolation_utils

#endif // EXTRAPOLATION_UTILS_h