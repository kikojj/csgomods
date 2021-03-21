#pragma once

#define VAR_R_DEC(type, name) type name();
#define VAR_R_P_DEC(type, name, paramType) type name(paramType);
#define VAR_R_DEF(type, name, className, base, offsetType)  type className::name(){\
                                                              auto name = mem.read<type>(base + Offsets::offsetType::name);\
                                                              return name;\
                                                            }
#define VAR_R_DEF_OFFNAME(type, name, className, base, offsetType, offsetName)  type className::name(){\
                                                              auto name = mem.read<type>(base + Offsets::offsetType::offsetName);\
                                                              return name;\
                                                            }
#define VAR_R_DEF_DEBUG(type, name, className, base, offsetType)  type className::name(){\
                                                                    auto name = mem.read<type>(base + Offsets::offsetType::name);\
                                                                    std::cout << #name << name << std::endl;\
                                                                    return name;\
                                                                  }

#define VAR_W_DEC(type, name) void name(type);
#define VAR_W_DEF(type, name, className, base, offsetType)  void className::name(type value){\
                                                              mem.write(base + Offsets::offsetType::name, value);\
                                                            }
#define VAR_W_DEF_OFFNAME(type, name, className, base, offsetType, offsetName)  void className::name(type value){\
                                                              mem.write(base + Offsets::offsetType::offsetName, value);\
                                                            }

#define VAR_RW_DEC(type, name)  VAR_R_DEC(type, name)\
                                VAR_W_DEC(type, name)
#define VAR_RW_DEF(type, name, className, base, offsetType)   VAR_R_DEF(type, name, className, base, offsetType)\
                                                              VAR_W_DEF(type, name, className, base, offsetType)
#define VAR_RW_DEF_OFFNAME(type, name, className, base, offsetType, offsetName)   VAR_R_DEF_OFFNAME(type, name, className, base, offsetType, offsetName)\
                                                                                  VAR_W_DEF_OFFNAME(type, name, className, base, offsetType, offsetName)