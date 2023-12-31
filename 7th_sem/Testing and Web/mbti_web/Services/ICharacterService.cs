﻿using mbti_web.Entities;
using mbti_web.Models;

namespace mbti_web.Services
{
    public interface ICharacterService
    {
        List<CharacterModel> GetAllCharacters();
        CharacterModel GetCharacterByID(int id);
        List<CharacterModel> GetCharacterByType(int type);
        List<CharacterModel> GetCharacterByType(string type);
        List<CharacterModel> GetCharacterByStrLike(string _str, int _flag);
        void AddCharacter(CharacterModel charModel);
        void UpdateType(CharacterModel charModel);
    }
}
