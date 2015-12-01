#include <hpx/hpx_init.hpp>
#include <hpx/components/iostreams/standard_streams.hpp>
#include <hpx/async.hpp>
#include <hpx/lcos/wait_all.hpp>
#include <hpx/lcos/when_all.hpp>

template <typename RandomAccessIterator>
void
quick_sort(RandomAccessIterator first, RandomAccessIterator limit)
{
    const auto size = std::distance(first, limit);
    if(size < 1000){
        std::sort(first,limit);
        return;
    }

    const auto pivot = first + size/2;
    hpx::future<void> nth = hpx::async([pivot, first, limit]{
            std::nth_element(first, pivot, limit);
        });

    hpx::future<hpx::util::tuple<hpx::future<void>, hpx::future<void> > > low_and_high
        = nth.then([=](hpx::future<void>) {
                return hpx::when_all(
                    hpx::async([=]{
                            quick_sort(first, pivot);
                        }),
                    hpx::async([=]{
                            quick_sort(pivot + 1, limit);
                        }));
        });
    hpx::wait_all(low_and_high);
}

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

        quick_sort(nums.begin(), nums.end());

        char const* fmt = "sort %1% elements with quick_sort \n elapsed time: %2% [s]\n";
        std::cout << (boost::format(fmt) % n % t.elapsed());
    }

    return hpx::finalize(); // Handles HPX shutdown
}

