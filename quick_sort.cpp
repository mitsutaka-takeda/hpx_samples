#include <hpx/hpx_init.hpp>
#include <hpx/components/iostreams/standard_streams.hpp>
#include <hpx/runtime/actions/plain_action.hpp>

template <typename RandomAccessIterator>
void
quick_sort(RandomAccessIterator first, RandomAccessIterator limit)
{
    const auto size = std::distance(first, limit);
    if(size < 2){
        return;
    }

    const auto pivot = first + size/2;
    std::nth_element(first, pivot, limit);
    quick_sort(first, pivot);
    quick_sort(pivot + 1, limit);
}

int main(int argc, char *argv[]) {
    boost::program_options::options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options()
        ( "n-value",
          boost::program_options::value<boost::uint64_t>()->default_value(10),
          "n value for the quick_sort function");

    return hpx::init(desc_commandline, argc, argv);
}

int hpx_main(boost::program_options::variables_map& vm){
    boost::uint64_t n = vm["n-value"].as<boost::uint64_t>();

    {
        std::vector<int> nums(n);
        std::iota(nums.begin(), nums.end(), 0);
        std::random_shuffle(nums.begin(), nums.end());

        hpx::util::high_resolution_timer t;

        quick_sort(nums.begin(), nums.end());

        char const* fmt = "sort %1% elements with quick_sort \n elapsed time: %2% [s]\n";
        std::cout << (boost::format(fmt) % n % t.elapsed());
    }

    return hpx::finalize(); // Handles HPX shutdown
}
