#include <hpx/hpx_init.hpp>
#include <hpx/components/iostreams/standard_streams.hpp>
#include <hpx/include/parallel_sort.hpp>
#include <hpx/parallel/execution_policy.hpp>
#include <hpx/lcos/wait_all.hpp>
#include <hpx/parallel/executors/parallel_executor.hpp>

#include <cassert>

int main(int argc, char *argv[]) {
    boost::program_options::options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options()
        ( "size-of-vector",
          boost::program_options::value<boost::uint64_t>()->default_value(10),
          "size of the vector for the quick_sort function");

    return hpx::init(desc_commandline, argc, argv);
}

int hpx_main(boost::program_options::variables_map& vm){
    boost::uint64_t n = vm["size-of-vector"].as<boost::uint64_t>();

    {
        std::vector<int> nums(n);
        std::iota(nums.begin(), nums.end(), 0);
        std::random_shuffle(nums.begin(), nums.end());

        hpx::util::high_resolution_timer t;
        
        hpx::wait_all(
            hpx::parallel::sort(
                hpx::parallel::parallel_task_execution_policy{}.on(hpx::parallel::parallel_executor()), 
                nums.begin(), 
                nums.end()
                ));

        char const* fmt = "sort %1% elements with quick_sort \n elapsed time: %2% [s]\n";
        std::cout << (boost::format(fmt) % n % t.elapsed());
        assert(std::is_sorted(nums.cbegin(), nums.cend()));
    }

    return hpx::finalize(); // Handles HPX shutdown
}

