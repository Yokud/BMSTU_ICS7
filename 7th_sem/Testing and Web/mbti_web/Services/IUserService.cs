﻿using System.Collections.Generic;
using System.Threading.Tasks;
using mbti_web.Models;
using mbti_web.Entities;

namespace mbti_web.Services
{
    public interface IUserService
    {
        AuthenticateResponse Authenticate(AuthenticateRequest model);
        //Task<AuthenticateResponse> Register(AuthenticateRequest userModel);
        void Register(AuthenticateRequest userModel);
        List<UserModel> GetAll();
        UserModel GetById(int id);
        UserModel GetByLogin(string login);
        User GetByIdUser(int id);
        bool CheckLoginUnique(string Login);
        void UpdateUser(UserModel userModel);
        void DeleteUser(UserModel user);
        void AddUser(UserModel userModel);
    }
}
