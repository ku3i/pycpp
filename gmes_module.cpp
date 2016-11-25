/* This is a C API for accessing the GMES module from python */

#include <assert.h>
#include <learning/sensorspace.h>
#include <learning/payload.h>
#include <learning/expert.h>
#include <learning/gmes.h>
#include <common/log_messages.h>


class test_space : public sensor_vector {
    double y[3];

public:
    test_space()
    : sensor_vector(2) //TODO make flexible dimension
    , y{0.00, 0.00}
    {
        sensors.emplace_back("[1]" , [this](){ return this->y[0]; });
        sensors.emplace_back("[2]" , [this](){ return this->y[1]; });
    }

    void execute_cycle(double* data, unsigned N) {
        assert(N == 2);
        for (unsigned int n = 0; n < N; ++n)
            y[n] = data[n];
        sensor_vector::execute_cycle();
    }
};

class gmesmodule {
public:
    gmesmodule(unsigned number_of_experts, double local_learning_rate, double gmes_learning_rate, unsigned experience_size)
    : sensors()
    , payloads(number_of_experts)
    , experts(number_of_experts, sensors, payloads, local_learning_rate, experience_size)
    , gmes(experts, gmes_learning_rate)
    { dbg_msg("Done creating gmes."); }

    void execute_cycle(double* data, unsigned N) {
//        for (unsigned int i=0; i < N; ++i)
//            std::cout << data[i] << " ";
//        std::cout << std::endl;
        sensors.execute_cycle(data, N);
        gmes.execute_cycle();
    }

    ~gmesmodule() { dbg_msg("Destroying gmes module."); }

private:
    test_space                   sensors;
    static_vector<Empty_Payload> payloads;
    Expert_Vector                experts;
    GMES                         gmes;
};

extern "C" {
    gmesmodule* gmes_new(unsigned number_of_experts, double local_learning_rate, double gmes_learning_rate, unsigned experience_size) {
        return new gmesmodule(number_of_experts, local_learning_rate, gmes_learning_rate, experience_size);
    }
    void gmes_del(gmesmodule* gmes) { if (gmes != NULL) delete gmes; else wrn_msg("gmes already deleted."); }

    void gmes_execute_cycle(gmesmodule* gmes, double* data, unsigned N) { gmes->execute_cycle(data, N); }
}
