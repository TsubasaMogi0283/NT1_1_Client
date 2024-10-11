#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <cassert>
#include <iostream>

#pragma comment(lib,"WSock32.lib")

int main() {

	//��{�I�ɂ̓T�[�o�[���Ɠ���������
	//bind�Alisten�͂��Ȃ���

	WSADATA wsaData;

	//Winsock�̏�����
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		//�������G���[
		std::cout << "WinSock�̏������Ɏ��s���܂���" << std::endl;
		return 1;
	}



	unsigned short uport= 8000;
	std::cout << "�|�[�g�ԍ�����͂��Ă�������" << std::endl;
	std::cin >> uport;





	// �T�[�o���܂��̓T�[�o��IP�A�h���X�����
	char sizeServer[1024] = {};
	std::cout<<"IP�A�h���X -->";
	std::cin >> sizeServer;
	fflush(stdin);



	//socket(�A�h���X�t�@�~��,�\�P�b�g�^�C�v,�v���g�^�C�v)
	//���s�����INVALID_SOCKET
	// 
	//�A�h���X�t�@�~��...�l�b�g���[�N�̃A�h���X�̎�ނ�\��
	//�\�P�b�g�^�C�v...SOCK_STREAM��SOCK_DREAM��2������
	//SOCK_STREAM...�M����������TCP�ʐM
	//SOCK_DREAM...�M����������TCP�ʐM

	//�v���g�R��...��{�I��0�B�f�t�H���g�̃v���g�R�����g����
	//�\�P�b�g�̍쐬
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	assert(s != INVALID_SOCKET);
	std::cout << "�\�P�b�g�����ɐ������܂���" << std::endl;


	

	//�T�[�o�[�𖼑O�Ŏ擾����
	HOSTENT* lpHost;
	unsigned int addr=0u;
	lpHost = gethostbyname(sizeServer);
	if (lpHost == NULL) {
		/* �T�[�o�[��IP�A�h���X�Ŏ擾���� */
		addr = inet_addr(sizeServer);
		lpHost = gethostbyaddr((char*)&addr, 4, AF_INET);
	}

	//�N���C�A���g�\�P�b�g���T�[�o�[�ɐڑ�
	SOCKADDR_IN saddr;
	memset(&saddr, 0, sizeof(SOCKADDR_IN));
	saddr.sin_family = lpHost->h_addrtype;
	saddr.sin_port = htons(uport);
	saddr.sin_addr.s_addr = *((u_long*)lpHost->h_addr);


	if (connect(s, (SOCKADDR*)&saddr, sizeof(saddr)) == SOCKET_ERROR) {
		std::cout << "�T�[�o�[�Ɛڑ��ł��܂���ł���" << std::endl;
		//�\�P�b�g�����
		closesocket(s);
		return 1;
	}





	//�ڑ���̃N���C�A���g���Ƃ̕�������Ƃ�
	//accept�֐��̕Ԃ�l��SOCKET�ϐ��us�v�Ɋi�[
	while (1) {
		int nRcv;
		char sizeBuffer[1024] = {};

		//�ڑ���̏���(�f�[�^���M)
		//recv(accept�̕Ԃ�l,��M������|�C���^,��M������̒���,��M�t���O)
		std::cout << "���M-->" << sizeBuffer;
		std::cin >> sizeBuffer;
		fflush(stdin);

		send(s, sizeBuffer, (int)strlen(sizeBuffer), 0);

		//recv(accept�̕Ԃ�l,��M������|�C���^,��M������̒���,��M�t���O)
		nRcv = recv(s, sizeBuffer, sizeof(sizeBuffer) - 1, 0);
		sizeBuffer[nRcv] = '\0';
		std::cout << "��M-->"<< sizeBuffer << std::endl;;



	}

	//�\�P�b�g�����
	closesocket(s);

	//Winsock�̏I��
	WSACleanup();

	return 0;


}
