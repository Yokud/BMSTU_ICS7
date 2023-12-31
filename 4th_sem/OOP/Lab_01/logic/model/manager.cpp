#include "manager.h"

error_t manager(model2D_t &model2D, const params_t &params, const task_t &task)
{
    error_t err = OK;
    static model3D_t model = init_model3D();

    switch (task) {
        case READ:
            err = read_model(model, params.load_params);
        break;

        case WRITE:
            err = write_model(model, params.load_params);
        break;

        case SCALE:
            err = scale_model(model, params.scale_params);
        break;

        case ROTATE:
            err= rotate_model(model, params.rotate_params);
        break;

        case PROJECTION:
            err = projection_model(model2D, params.proj_params, model);
        break;

        case DESTROY:
            delete_model3D(model);
        break;

        default:
            err= INCORRECT_COMMAND;
        break;
    }

    return err;
}
