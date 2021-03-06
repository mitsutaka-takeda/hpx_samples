#include <hpx/hpx_init.hpp>
#include <hpx/components/iostreams/standard_streams.hpp>
#include <hpx/runtime/actions/plain_action.hpp>

// forward declaration of the Fibonacci function
boost::uint64_t fibonacci(boost::uint64_t n);
HPX_PLAIN_ACTION(fibonacci, fibonacci_action);


boost::uint64_t
fibonacci(boost::uint64_t n)
{
    if (n < 2)
        return n;

    // We restrict ourselves to execute the Fibonacci function locally.
    hpx::naming::id_type const locality_id = hpx::find_here();

    // Invoking the Fibonacci algorithm twice is inefficient.
    // However, we intentionally demonstrate it this way to create some
    // heavy workload.

    fibonacci_action fib;
    hpx::future<boost::uint64_t> n1 = hpx::async(fib, locality_id, n - 1);
    hpx::future<boost::uint64_t> n2 = hpx::async(fib, locality_id, n - 2);

    return n1.get() + n2.get();   // wait for the Futures to return their values
}

int main(int argc, char *argv[])
{
   // Configure application-specific options
    boost::program_options::options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options()
        ( "n-value",
          boost::program_options::value<boost::uint64_t>()->default_value(10),
          "n value for the Fibonacci function")
        ;

    // Initialize and run HPX
    return hpx::init(desc_commandline, argc, argv);
}

int hpx_main(boost::program_options::variables_map& vm){
    // extract command line argument, i.e. fib(N)
    boost::uint64_t n = vm["n-value"].as<boost::uint64_t>();

    {
        // Keep track of the time required to execute.
        hpx::util::high_resolution_timer t;

        // Wait for fib() to return the value
        fibonacci_action fib;
        boost::uint64_t r = fib(hpx::find_here(), n);

        char const* fmt = "fibonacci(%1%) == %2%\nelapsed time: %3% [s]\n";
        std::cout << (boost::format(fmt) % n % r % t.elapsed());
    }

    return hpx::finalize(); // Handles HPX shutdown
}
