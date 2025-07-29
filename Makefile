Name:=Tenis

CC:=emcc
RUN:=emrun
MKDIR:=mkdir
RM:=rm -rf
ZIP:=zip
CP:=cp

SRC_DIRS:=src
INC_DIRS:=$(SRC_DIRS)
BIN_DIR:=bin
OBJ_DIR:=obj

SRCS:=$(wildcard $(addsuffix /*.cpp, $(SRC_DIRS)))
OBJS:=$(addprefix $(OBJ_DIR)/, $(patsubst %.cpp, %.o, $(SRCS)))

HEADS:=$(wildcard $(addsuffix /*.hpp, $(INC_DIRS)))

INC:=$(addprefix, -I, $(INC_DIRS))
LFLAGS:=-s USE_GLFW=3 -DPLATFORM_WEB -lglfw -L./lib/ -lraylib --preload-file resources -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1
CFLAGS:=-std=c++23

OUT_DIRS:=$(addprefix $(OBJ_DIR)/, $(SRC_DIRS))
OUT:=$(BIN_DIR)/index.js
HTML:=index.html
OUT_ZIP:=build.zip

.PHONY: run
run: $(OUT)
	$(RUN) $(BIN_DIR)/$(HTML)

.PHONY: zip
zip: $(OUT_ZIP)
$(OUT_ZIP): $(OUT)
	$(ZIP) $(OUT_ZIP) $(BIN_DIR)/*

$(OUT): $(OBJS)
	$(CP) $(HTML) $(BIN_DIR)/$(HTML)
	$(CC) $(INC) $^ $(CFLAGS) $(LFLAGS) -o $@ $(PRELOAD)

$(OBJ_DIR)/%.o: %.cpp $(HEADS)
	$(CC) $(INC) $(CFLAGS) -c $< -o $@ 

.PHONY: clean
clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(BIN_DIR)
	$(MKDIR) $(OBJ_DIR) $(BIN_DIR) $(OUT_DIRS)
