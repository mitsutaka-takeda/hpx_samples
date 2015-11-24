#include <hpx/hpx_init.hpp>
#include <hpx/components/iostreams/standard_streams.hpp>

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

int hpx_main(boost::program_options::variables_map&){

    hpx::cout << "Hello world!\n";
    return hpx::finalize();
}
