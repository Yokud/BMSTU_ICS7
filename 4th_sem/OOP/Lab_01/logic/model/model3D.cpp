#include "model3D.h"

model3D_t init_model3D()
{
    model3D_t model;
    model.loaded = false;
    init_points3D(model.points);
    init_edges(model.edges);
    return model;
}

void delete_model3D(model3D_t &model)
{
    model.loaded = false;
    delete_edges(model.edges);
    delete_points3D(model.points);
}

bool is_loaded(const model3D_t &model)
{
    return model.loaded;
}

error_t scale_model(model3D_t &model, const scale_params_t &params)
{
    error_t err = OK;

    if (!is_loaded(model))
        err = MODEL_VOID_ERROR;

    if (err == OK)
        scale_points3D(model.points, params);
    return err;
}

static bool is_incorrect_axis(const axis_t &axis)
{
    return axis != AXIS_X && axis != AXIS_Y && axis != AXIS_Z;
}

error_t rotate_model(model3D_t &model, const rotate_params_t &params)
{
    error_t err = OK;

    if (!is_loaded(model))
        err = MODEL_VOID_ERROR;

    if (err == OK && is_incorrect_axis(params.axis))
        err = ROTATION_AXIS_ERROR;

    if (err == OK)
        rotate_points3D(model.points, params);
    return err;
}

error_t write_model(model3D_t &model, const load_params_t &params)
{
    if (!is_loaded(model))
        return MODEL_VOID_ERROR;

    error_t err = OK;

    FILE *f = NULL;
    if (err == OK && (f = fopen(params.filename, "w")) == NULL)
        err = FILE_ERROR;

    if (err == OK)
    {
        write_points3D(f, model.points);
        write_edges(f, model.edges);
    }

    fclose(f);
    return err;
}

static bool is_correct_model(model3D_t &model)
{
    error_t err;
    err = are_correct_edges(model.edges, model.points);

    if (err == OK)
        model.loaded = true;

    return err == OK;
}

// исправить проверку загруженности модели - Fixed!
error_t read_model(model3D_t &model, const load_params_t &params)
{

//    if (is_loaded(model))
//        return MODEL_ALREADY_LOADED_ERROR;

    FILE *f = NULL;

    if ((f = fopen(params.filename, "r")) == NULL)
        return FILE_ERROR;

    error_t err = OK;
    model3D_t model_tmp = init_model3D();
    err = read_points3D(model_tmp.points, f);
    if (err == OK)
    {
        err = read_edges(model_tmp.edges, f);
        if (err != OK)
            delete_points3D(model_tmp.points);
    }
    fclose(f);

    bool is_correct;
    if (err == OK && (is_correct = is_correct_model(model_tmp)))
    {
        delete_model3D(model);
        model = model_tmp;
    }
    else if (!is_correct)
        err = INCORRECT_MODEL;

    if (err == OK)
        init_scene(model.scene_params, model.points);

    return err;
}

error_t projection_model(model2D_t &model2D, const projection_params_t &params, const model3D_t &model)
{
    if (!model.loaded)
        return MODEL_VOID_ERROR;

    error_t err = projection_points3D(model2D.points2D, model.points, model.scene_params);

    if (err == OK)
        transl_to_screen_coords_points2D(model2D.points2D, model.scene_params, params.screen_params);

    if (err == OK)
    {
        err = copy_edges(model2D.edges, model.edges);
        if (err != OK)
            delete_points2D(model2D.points2D);
    }

    return err;
}
