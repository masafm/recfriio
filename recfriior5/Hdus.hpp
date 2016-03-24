// HDUS

#ifndef _HDUS_H_
#define _HDUS_H_

#include "Recordable.hpp"
#include "AbstractFriio.hpp"


class Hdus : public AbstractFriio
{
    uint8_t saddr;

    uint8_t* buffer;
    size_t buffersize;
    size_t buffer_remainsize;

public:
	Hdus();
        virtual ~Hdus();
	virtual void setChannel(BandType band, int channel);
	virtual const float getSignalLevel(void);
	virtual int getStream(const uint8_t** bufp, int timeoutMsec);
	
protected:

	/**
	 * デバイスファイルがFriioの物かを確認する。
	 * @param devfile デバイスファイル
	 * @return Friioである場合true;
	 */
	virtual bool is_friio(const std::string &devfile);

	/**
	 * 固定処理A(デバイス判定)
	 * @param fd 対象ファイルディスクリプタ
	 * @return TunerType チューナの種別
	 */
	virtual TunerType UsbProcFixInitA(int fd);

	/**
	 * 初期化処理 : 処理開始
	 * 便宜上Beginにしているが、本来どんなことをしているかは不明
	 * @param fd 対象ファイルディスクリプタ
	 */
	virtual void UsbProcBegin(int fd);
	
	/**
	 * 処理終了
	 * 便宜上Endにしている。恐らくバッファクリア
	 * @param fd 対象ファイルディスクリプタ
	 */
	virtual void UsbProcEnd(int fd);
	
	/**
	 * 初期化処理 : ストリーム制御データ
	 * @param fd 対象ファイルディスクリプタ
	 */
	virtual void UsbProcStreamInit(int fd);

	/**
	 * ＬＥＤ制御
	 * @param fd 対象ファイルディスクリプタ
	 * @param color 色
	 */
	virtual void UsbProcLED(int fd, BonLedColor color, bool lnb_powered);
	
	/**
	 * 初期化処理 : 固定処理B
	 * @param fd 対象ファイルディスクリプタ
	 */
	virtual void UsbProcFixInitB(int fd);

private:

    uint8_t r5;

    void send_ctl(uint8_t *data, int fd, uint8_t req, uint16_t val, uint16_t idx, uint16_t len);

};

#endif
