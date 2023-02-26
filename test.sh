make all
echo "DIFF BETWEEN VECTORS"
./vector > vector_a; ./vector_std > vector_b; diff vector_a vector_b
echo "DIFF BETWEEN STACKS"
./stack > stack_a; ./stack_std > stack_b; diff stack_a stack_b
echo "DIFF BETWEEN MAPS"
./map > map_a; ./map_std > map_b; diff map_a map_b
rm -rf vector_a vector_b stack_a stack_b map_a map_b