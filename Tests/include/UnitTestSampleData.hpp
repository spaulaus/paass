///@file UnitTestSampleData.hpp
///@brief This header provides sample data that can be used by Unit Tests to
/// ensure proper functionality.
///@author S. V. Paulauskas
///@date December 18, 2016

#ifndef PIXIESUITE_UNITTESTSAMPLEDATA_HPP
#define PIXIESUITE_UNITTESTSAMPLEDATA_HPP

#include <string>
#include <tuple>
#include <utility>
#include <vector>

///@TODO This whole file needs to be reorganized. This information is repeated a bunch. Maybe consider a function that will
/// construct the headers for us?

///This namespace contains the raw channel information that was used to construct the headers in the unittest_encoded_data
/// namespace. These values are also used when testing the data encoding.
namespace unittest_decoded_data {
    extern const unsigned int channelNumber;
    extern const unsigned int crateId;
    extern const unsigned int expected_size;
    extern const unsigned int ts_high;
    extern const unsigned int ts_low;
    extern const unsigned int cfd_fractional_time;
    extern const unsigned int slotId;
    extern const unsigned int energy;
    extern const unsigned int ex_ts_high;
    extern const unsigned int ex_ts_low;
    extern const bool cfd_forced_trigger;
    extern const bool cfd_source_trigger_bit;
    extern const bool pileup_bit;
    extern const bool trace_out_of_range;
    extern const bool virtual_channel;
    extern const double filterBaseline;

    extern const std::vector<unsigned int> energy_sums;

    extern const std::vector<unsigned int> qdc;

    //Need to figure out where to put these as they are Firmware / Frequency
    // specific values. They are for R30747, 250 MS/s.
    namespace R30474_250 {
        extern const double ts;
        extern const double ts_w_cfd;
    }
}

///This namespace contains Firmware / Frequency specific headers that are used to test the decoding of data. The headers that
/// we have here include the 2 words that are inserted by poll2 so that the XiaListModeDataDecoder::DecodeBuffer method will
/// function properly.
namespace unittest_encoded_data {
    //A buffer with zero length
    extern const std::vector<unsigned int> empty_buffer;

    //A buffer that for an empty module
    extern const std::vector<unsigned int> empty_module_buffer;

    ///A header with a header length 20 instead of the true header length 4
    extern const std::vector<unsigned int> header_w_bad_headerlen;

    ///A header where the event length doesn't match what it should be.
    extern const std::vector<unsigned int> header_w_bad_eventlen;

    extern const unsigned int encodedFilterBaseline;

    namespace R30474_250 {
        extern const std::string test_firmware;
        extern const unsigned int test_frequency;

        extern const unsigned int word0_header;
        extern const unsigned int word0_headerWithExternalTimestamp;
        extern const unsigned int word0_headerWithEsums;
        extern const unsigned int word0_headerWithEsumsExternalTimestamp;
        extern const unsigned int word0_headerWithQdc;
        extern const unsigned int word0_headerWithQdcExternalTimestamp;
        extern const unsigned int word0_headerWithEsumsQdc;
        extern const unsigned int word0_headerWithEsumsQdcExternalTimestamp;
        extern const unsigned int word0_headerWithTrace;
        extern const unsigned int word1;
        extern const unsigned int word2_energyOnly;
        extern const unsigned int word2_energyWithCfd;
        extern const unsigned int word3_headerOnly;
        extern const unsigned int word3_headerWithTrace;

        /// Just the header, including the first two words inserted by poll2
        extern const std::vector<unsigned int> header;

        /// This header has the CFD fractional time.
        extern const std::vector<unsigned int> headerWithCfd;

        /// Header that includes an external time stamp.
        extern const std::vector<unsigned int> headerWithExternalTimestamp;

        ///Header that has Esums
        extern const std::vector<unsigned int> headerWithEnergySums;

        ///Header that has Esums and an External Timestamp
        extern const std::vector<unsigned int> headerWithEnergySumsExternalTimestamp;

        ///A header that also contains a QDC
        extern const std::vector<unsigned int> headerWithQdc;

        ///Header that has QDCs and External Timestamps
        extern const std::vector<unsigned int> headerWithQdcExternalTimestamp;

        ///Header that has Esums and a QDC
        extern const std::vector<unsigned int> headerWithEnergySumsQdc;

        ///Header that has Esums, QDC, and External Timestamp
        extern const std::vector<unsigned int> headerWithEnergySumsQdcExternalTimestamp;

        //The header is the standard 4 words. The trace is 62 words, which gives a trace length of 124. This gives us an event
        // length of 66. We have 2 words for the Pixie Module Data Header.
        extern const std::vector<unsigned int> headerWithTrace;

        extern const std::vector<unsigned int> headerWithQdcTrace;
    }
}

namespace unittest_cfd_variables {
    namespace traditional {
        extern const double fraction;
        extern const unsigned int delay;
        extern const double phase;
    }

    namespace xia {
        extern const double fraction;
        extern const unsigned int delay;
        extern const double phase;
    }

    namespace polynomial {
        extern const double fraction;
        extern const unsigned int delay;
        extern const double phase;
    }
}

namespace unittest_fit_variables {
    //Set the <beta, gamma> for the fitting from the results of a gnuplot script
    namespace pmt{
        extern const double beta;
        extern const double gamma;
        extern const double phase;
    }

    namespace gaussian {
        extern const double beta;
        extern const double gamma;
        extern const double phase;
    }
}

namespace unittest_trace_variables {
    //This is a trace taken using a 12-bit 250 MS/s module from a medium VANDLE module.
    extern const std::vector<unsigned int> trace;

    extern const std::vector<double> trace_sans_baseline;
    
    extern const unsigned int length;
    extern const unsigned int gap;
    extern const std::vector<double> filteredTrace;

    extern const std::pair<unsigned int, unsigned int> waveform_range;

    extern const std::vector<double> waveform;

    extern const double waveform_qdc;

    extern const std::vector<unsigned int> const_vector_uint;
    extern const double maximum_value;
    extern const unsigned int max_position;
    extern const std::pair<unsigned int, double> max_pair;

    extern const double baseline;
    extern const double standard_deviation;
    extern const std::pair<double, double> baseline_pair;

    extern const unsigned int trace_delay;
    extern const double tail_ratio;

    extern const std::vector<double> extrapolated_max_coeffs;
    extern const double extrapolated_maximum;
    extern const std::pair<unsigned int, double> extrapolated_maximum_pair;
}

namespace unittest_gaussian_trace {
    extern const std::vector<double> waveform;

    extern const unsigned int maxPosition;
    extern const double maxValue;
    extern const std::pair<unsigned int, double> maxPair;

    extern const double baseline;
    extern const double standardDeviation;
    extern const std::pair<double, double> baselinePair;
    extern const double qdc;
    extern const double sigma;
}

namespace unittest_helper_functions {
    extern const std::pair<double, double> xy1;
    extern const std::pair<double, double> xy2;
    extern const double slope;
    extern const double intercept;

    extern const std::vector<unsigned int> integration_data;
    extern const double integral;

    extern const std::pair<unsigned int, unsigned int> qdc_pair;
    extern const double integration_qdc;

    extern const std::vector<unsigned int> poly3_data;
    extern const double poly3_maximum;

    //A vector containing the coefficients obtained from gnuplot using the data
    // from pol3_data with an x value starting at 0
    extern const std::vector<double> poly3_coeffs;

    extern const std::vector<unsigned int> poly2_data;
    extern const double poly2_val;
    extern const std::vector<double> poly2_coeffs;

    extern const unsigned int leading_edge_position;
    extern const double leading_edge_fraction;
    extern const double bad_fraction;
}

#endif //PIXIESUITE_UNITTESTEXAMPLETRACE_HPP_HPP
